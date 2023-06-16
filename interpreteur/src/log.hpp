#ifndef LOG
#define LOG

class Log
{
public:
	
	bool error = false;

	void AddError(Error );
	Error GetError();

private:
    list<Error> errorList;
};

#endif