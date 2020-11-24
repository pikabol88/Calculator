#ifndef ERROR_H
#define ERROR_H
#include <string>

class ErrorState {
public:
    
    typedef enum errorState {
        SUCCESS,
        ERROR_BRACKETS,
        ERROR_OPERATION,
        ERROR_FUNCTION,
    } error_state_t;
   
    ErrorState();

private:
    static error_state_t calc_error;


    static error_state_t getErrorState();
    static void setErrorState(error_state_t error);
    static std::string getErrorMessage();
};
#endif //ERROR_H
