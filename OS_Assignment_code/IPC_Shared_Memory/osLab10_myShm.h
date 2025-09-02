#deﬁne NOT_READY -1
#deﬁne FILLED 0
#deﬁne TAKEN 1
struct Memory {
int status; // for sync server & client
int data[4];
};