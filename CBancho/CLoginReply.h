#pragma once
#include "Includes.h"
#include "CBanchoHelper.hpp"
#include "CPacket.h"

class CLoginReply : public CPacket {
	UserLogin user;
public:

	CLoginReply(UserLogin user) {
		// todo auth login somewhere
		this->user = user;
	}

	void WriteToStream(int socket) override {
		CBanchoHelper::Write<int16_t>(socket, 5);
		CBanchoHelper::Write<byte>(socket, 0);
		CBanchoHelper::Write<int32_t>(socket, 4);
		CBanchoHelper::Write<int32_t>(socket, 1);
	}
};