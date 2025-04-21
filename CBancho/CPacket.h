class CPacket {
public:
	virtual void WriteToStream(int socket) = 0;
};