#pragma once
#include "Includes.h"

namespace CBanchoHelper {
    bool readAll(int sock, void* buffer, size_t length) {
        size_t totalReceived = 0;
        while (totalReceived < length) {
            int received = recv(sock, (char*)buffer + totalReceived, length - totalReceived, 0);
            if (received <= 0) return false;
            totalReceived += received;
        }
        return true;
    }
	template<typename T>
    bool Read(int socket, T& out) {
        uint8_t buffer[sizeof(T)];
        if (!readAll(socket, buffer, sizeof(T))) return false;

        out = 0;

        for (size_t i = 0; i < sizeof(T); i++) {
            out |= static_cast<T>(buffer[i]) << (8 * i);
        }
        return true;
    }
    template<typename T>
    static bool Write(int socket, T value) {
        uint8_t buffer[sizeof(T)];
        std::memcpy(buffer, &value, sizeof(T));
        return send(socket, reinterpret_cast<const char*>(buffer), sizeof(T), 0) != SOCKET_ERROR;
    }
    std::string ReadLine(int socket) {
        std::string result;
        char ch;

        while (true) {
            int res = recv(socket, &ch, 1, 0);
            if (res <= 0) break;
            if (ch == '\n') break;
            if (ch != '\r') result += ch;
        }
        return result;
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;

        while (std::getline(ss, item, delimiter)) {
            result.push_back(item);
        }

        return result;
    }
    UserLogin parseLoginLines(int socket) {
        UserLogin result;
        result.username = ReadLine(socket);
        result.password = ReadLine(socket);
        auto line = ReadLine(socket);
        auto dataparts = split(line, '|');
        result.build = dataparts[0];
        result.UtcOffset = std::stoi(dataparts[1]);
        result.DisplayCityLocation = dataparts[2] == "1" ? true : false;
        return result;
    }
};