#ifndef ERROR_H
#define ERROR_H
#include <string>

class ErrorState {
public:
    
    typedef enum errorState {
        SUCCESS,
        ERROR_POINT,
        ERROR_BRACKETS,
        ERROR_OPERATION,
        ERROR_FUNCTION,
        ERROR_EMPTY_BRACKETS,
    } error_state_t;
   
    static error_state_t getErrorState();
    static void setErrorState(error_state_t const &error);
    static std::string getErrorMessage();
    static bool isSuccess();

private:
    static error_state_t calc_error;
};
#endif //ERROR_H
