#include"save.h"

Saves::Saves(int slotCount) {
	initSavesFolder();
	vector<string> existingFilePath;
	getJustCurrentFile(SAVES_FOLDER, existingFilePath);
	int i = 0;
	for (i; i < slotCount&&i < existingFilePath.size(); i++) {
		slots.push_back(SaveSlot(i, existingFilePath[i], SAVES_FOLDER));
	}
	for (i; i < slotCount; i++)
	{
		slots.push_back(SaveSlot(i, SAVES_FOLDER));
	}
}

SaveSlot Saves::createNewSave() {
	for (SaveSlot slot : slots) 
	{
		if (slot.isEmpty()) {
			slot.createFile();
			return slot;
		}
	}
	return SaveSlot(0, "");
}

SaveSlot Saves::getSaveSlot(int number) {
	if (number < slots.size()) {
		return slots[number];
	}
	return SaveSlot(0, "");
}

list<SaveSlot> Saves::getCorruptSaves() {
	list<SaveSlot> corrupts;
	for (SaveSlot slot : slots) {
		if (slot.isCorrupt()) {
			corrupts.push_back(slot);
		}
	}
	return corrupts;
}

SaveSlot Saves::getFirstWorld() {
	for (SaveSlot slot : slots) {
		if (!slot.isEmpty() && !slot.isCorrupt()) {
			return slot;
		}
	}
	return slots[0];
}

