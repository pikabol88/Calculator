#include "error.h"


ErrorState::ErrorState() {}

ErrorState::error_state_t ErrorState::calc_error = ErrorState::errorState::SUCCESS;

ErrorState::error_state_t ErrorState::getErrorState()
{
    return calc_error;
}

void ErrorState::setErrorState(error_state_t error) {
    calc_error = error;
}



std::string ErrorState::getErrorMessage() {
    std::string message;
    switch (calc_error)
    {
    case ERROR_BRACKETS:
        message = "ERROR: check the input -> problem is the number of brackets";
        break;
    case ERROR_OPERATION:
        message = "ERROR: check the input ->  problem is the unsupported operation";
        break;
    case ERROR_FUNCTION:
        message = "ERROR: check the input ->  problem is the unsupported function";
        break;
    default:
        break;
    }
    return message;
};