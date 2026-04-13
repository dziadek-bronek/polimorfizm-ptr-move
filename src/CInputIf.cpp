#include "include/CInput.hpp"

CInputIf::~CInputIf() {}

CInputIf* CInputIf::createNew()
{
    return createNewCInput();
}
