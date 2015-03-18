/*
 * tape.cpp
 *
 *  Created on: 15/03/2015
 *      Author: raster
 */

#include "tape.hh"
#include "z80free/Z80free.h"

#include <stdio.h>
#include <string.h>

class TapeBlock {

private:
	class TapeBlock *next;
	uint8_t signal;
protected:
	uint32_t counter0;
	uint32_t counter1;
	bool zero_first;
public:

	TapeBlock() {
		this->next = NULL;
		this->signal = 0;
		this->counter0 = 0;
		this->counter1 = 0;
		this->zero_first = true;
	}

	virtual ~TapeBlock() {

		if (this->next != NULL) {
			delete (this->next);
		}
	}

	virtual bool fast_load(uint8_t *data, uint16_t &size, uint8_t &flag) = 0;

	/**
	 * Adds a new block to the end of the list
	 * @param block The block to add to the list
	 */
	void add_block(class TapeBlock *new_block) {

		if (this->next == NULL) {
			this->next = new_block;
		} else {
			this->next->add_block(new_block);
		}
	}

	/**
	 * Returns the next block in the list
	 * @return The block next to this one
	 */
	class TapeBlock *next_block() {
		return this->next;
	}

	/**
	 * Returns the tape signal at the current instant
	 * @return Tape signal
	 */
	uint8_t read_signal() {

		return this->signal;
	}

	/**
	 * Emulates the block for the specified time
	 * @param tstates The number of tstates to emulate
	 * @return The number of tstates that remained to emulate because the block ended prematurely
	 */
	uint32_t play(uint32_t tstates) {

		if (this->zero_first) {
			if (this->counter0 > 0) {
				if (this->counter0 >= tstates) {
					this->counter0 -= tstates;
					this->signal = 0;
					return 0;
				} else {
					tstates -= this->counter0;
					this->counter0 = 0;
				}
			}
			if (this->counter1 > 0) {
				if (this->counter1 >= tstates) {
					this->counter1 -= tstates;
					this->signal = 1;
					return 0;
				} else {
					tstates -= this->counter1;
					this->counter1 = 0;
				}
			}
			return tstates;
		} else {
			if (this->counter1 > 0) {
				if (this->counter1 >= tstates) {
					this->counter1 -= tstates;
					this->signal = 1;
					return 0;
				} else {
					tstates -= this->counter1;
					this->counter1 = 0;
				}
			}
			if (this->counter0 > 0) {
				if (this->counter0 >= tstates) {
					this->counter0 -= tstates;
					this->signal = 0;
					return 0;
				} else {
					tstates -= this->counter0;
					this->counter0 = 0;
				}
			}
			return tstates;
		}
	}

	/**
	 * Sets the time values for the next bit to be read from the tape
	 * @return TRUE if there is a new bit; FALSE if there are no more bits in this block
	 */
	virtual bool next_bit() = 0;

	/**
	 * Resets a block to its initial state. Mandatory before starting working with it
	 */
	virtual void reset() {
	}
};

class TAPBlock : public TapeBlock {

	uint8_t *data;
	uint16_t data_size;
	uint8_t bit;
	uint32_t loop;
	int pointer;
	enum TAPBLOCK_states {TAPBLOCK_GUIDE, TAPBLOCK_DATA, TAPBLOCK_PAUSE} current_state;

	void set_state(enum TAPBLOCK_states new_state) {

		this->current_state = new_state;
		switch (new_state) {
		case TAPBLOCK_GUIDE:
			if (!(0x80 & this->data[0])) {
				this->loop = 3228; // 4 seconds
			} else {
				this->loop = 1614; // 2 seconds
			}
		break;
		case TAPBLOCK_DATA:
			this->pointer = 0;
			this->bit = 0x80;
		break;
		case TAPBLOCK_PAUSE:
		break;
		}
	}

public:
	TAPBlock(uint8_t *data,uint16_t size) :TapeBlock() {

		this->data = new uint8_t[size];
		this->data_size = size;
		memcpy(this->data,data,size);
		this->current_state = TAPBLOCK_GUIDE;
		this->loop = 0;
		this->pointer = 0;
		this->bit = 0x80;
		this->set_state(TAPBLOCK_GUIDE);
	}

	void reset() {
		this->counter0 = 0;
		this->counter1 = 0;
		this->set_state(TAPBLOCK_GUIDE);
	}

	bool next_bit() {

		bool current_bit;

		switch (this->current_state) {
		case TAPBLOCK_GUIDE:
			if (this->loop > 0) {
				// guide tone loop
				this->counter0 = 2168;
				this->counter1 = 2168;
				this->loop--;
			} else {
				// sync bit
				this->counter0 = 667;
				this->counter1 = 735;
				this->set_state(TAPBLOCK_DATA);
			}
			return true;
		break;
		case TAPBLOCK_DATA:
			if (this->bit == 0) {
				this->bit = 0x80;
				this->pointer++;
				if (this->pointer == this->data_size) {
					this->counter0 = 3500000; // one second
					this->counter1 = 0;
					this->set_state(TAPBLOCK_PAUSE);
					return true;
				}
			}
			current_bit = ((*(this->data+this->pointer)) & this->bit) == 0;
			if (current_bit) {
				this->counter0 = 852;
				this->counter1 = 852;
			} else {
				this->counter0 = 1710;
				this->counter1 = 1710;
			}
			this->bit /=2;
			return true;
		break;
		case TAPBLOCK_PAUSE:
			return false; // end of data
		break;
		}
		return true;
	}

	bool fast_load(uint8_t *data, uint16_t &size, uint8_t &flag) {
		flag = this->data[0];
		size = this->data_size - 2;
		memcpy(data,this->data+1,size);
		return true;
	}
};

Tape::Tape() {
	this->blocks = NULL;
	this->current_block = NULL;
	this->paused = true;
	this->block_accesed = false;
}

Tape::~Tape() {
	this->delete_blocks();
}

void Tape::add_block(class TapeBlock *new_block) {

	if (this->blocks == NULL) {
		this->blocks = new_block;
	} else {
		this->blocks->add_block(new_block);
	}
}

void Tape::delete_blocks() {

	delete (this->blocks);
	this->blocks = NULL;
	this->current_block = NULL;
	this->block_accesed = false;
}

bool Tape::load_file(char *filename) {
	char char_id[10];
	int retval;
	this->delete_blocks();

	this->paused = true;
	FILE *file = fopen(filename,"rb");
	if (file == NULL) {
		return true; // error while opening the file
	}
	retval=fread(char_id,10,1,file); // read the (maybe) TZX header
	fclose(file);
	if((!strncmp(char_id,"ZXTape!",7)) && (char_id[7]==0x1A)&&(char_id[8]==1)) {
		return this->load_tzx(filename);
	} else {
		return this->load_tap(filename);
	}
}

bool Tape::load_tap(char *filename) {

	FILE *file;
	uint8_t data[65536];
	uint16_t size;
	size_t retval;

	file = fopen(filename,"rb");
	if (file == NULL) {
		return true; // error while opening the file
	}
	do {
		// read block size
		retval = fread (data, 2, 1, file);
		if (retval < 1) {
			break; // end-of-file
		}
		size = ((unsigned int) data[0]) + 256 * ((unsigned int) data[1]);
		retval = fread (data, size, 1, file);
		if (retval != 1) {
			fclose(file);
			return (true); // end-of-file and error
		}
		this->add_block(new TAPBlock(data,size));
	} while(true);

	fclose(file);
	this->current_block = this->blocks;
	return false;
}

bool Tape::load_tzx(char *filename) {

	return false;
}

void Tape::play(uint32_t tstates) {

	uint32_t residue = tstates;

	if (this->current_block == NULL) {
		return;
	}

	if (this->paused) {
		return;
	}

	this->block_accesed = true;
	while(true) {
		residue = this->current_block->play(residue);
		if (residue != 0) {
			if (this->current_block->next_bit() == false) {
				this->current_block = this->current_block->next_block();
				if (this->current_block == NULL) {
					this->current_block = this->blocks;
				}
				this->current_block->reset();
				this->block_accesed = false;
			}
		} else {
			break;
		}
	}
}

uint8_t Tape::read_signal() {

	if (this->current_block == NULL) {
		return 0;
	} else {
		return this->current_block->read_signal();
	}
}

void Tape::rewind() {
	this->current_block = this->blocks;
	if (this->current_block != NULL) {
		this->current_block->reset();
	}
	this->block_accesed = false;
}

void Tape::set_pause(bool pause) {
	this->paused = pause;
}

enum FastLoadReturn Tape::fast_read(uint8_t *data, uint16_t &length,uint8_t flag) {

	uint8_t block_flag;

	if (this->blocks == NULL) {
		return FASTLOAD_NO_TAPE;
	}

	if (this->block_accesed) {
		if (this->current_block != NULL) {
			this->current_block = this->current_block->next_block();
		}
	}
	if (this->current_block == NULL) {
		return FASTLOAD_END_TAPE;
	}
	this->current_block->reset();
	this->block_accesed = true;

	if (!this->current_block->fast_load(data,length,block_flag)) {
		return FASTLOAD_NO_BLOCK;
	}
	if (block_flag != flag) {
		return FASTLOAD_NO_FLAG;
	}

	return FASTLOAD_OK;
}