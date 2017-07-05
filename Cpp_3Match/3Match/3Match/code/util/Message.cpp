#include "Message.h"
#include <gslib.h>
void Message::send(const std::string & _title, const std::string & _message)
{
	MessageBox((HWND)NULL, _message.c_str(), _title.c_str(), MB_OK);
}
