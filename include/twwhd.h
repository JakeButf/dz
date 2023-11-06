/*

VALUES FROM HERE:
https://docs.google.com/spreadsheets/d/1kloHL2zQztswThTgl3zMrl1hdGh8qb9AgaZWj6Powvw

Credits: Myself, BowserIsBored

*/
#include <cstdint>
#include <string>

#ifndef TWWHD_H
#define TWWHD_H
const uint32_t twwhd_currentHearts = 0x15073683;
typedef struct {
	const uint32_t pointer = 0x10989C74;
	const uint32_t animation_increment = pointer + 0x57C0; //the animations are read only (there's probably values that actually affect the animations but are unknown)
	const uint32_t animation_position = pointer + 0x57BC;
}twwhd_link;

#endif