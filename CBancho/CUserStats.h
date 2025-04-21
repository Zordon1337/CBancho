#pragma once
#include "Includes.h"
#include "CBanchoHelper.hpp"
class Status {
public:
	void WriteToStream(int socket) {

	}
};
class CUserStats : public CPacket {
public:

	CUserStats() {
	}

	void WriteToStream(int socket) override {
		CBanchoHelper::Write<int16_t>(socket, 11);
		CBanchoHelper::Write<byte>(socket, 0);
		CBanchoHelper::Write<int32_t>(socket, 35);
		CBanchoHelper::Write<int32_t>(socket, 1); // 4b (uid)
		CBanchoHelper::Write<byte>(socket, 1); // 1b (completeness)
		CBanchoHelper::Write<byte>(socket, 0); // 1b (StatusUpdate->Status)
		CBanchoHelper::Write<byte>(socket, 0); // 1b (StatusUpdate->BeatmapUpdate)
		CBanchoHelper::Write<long>(socket, 0); // 8b (RankedScore)
		CBanchoHelper::Write<float>(socket, 1); // 4b (Accuracy)
		CBanchoHelper::Write<int32_t>(socket, 0); // 4b (PlayCount)
		CBanchoHelper::Write<long>(socket, 0); // 8b (TotalScore)
		CBanchoHelper::Write<int32_t>(socket, 1); // 4b (Rank)




	}
};