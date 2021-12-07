#include "Tokenizer.h"

/*
 * void setString - sets the string to be used in the StringStream
 */

void Tokenizer::setString(const string& str)
{
	//sets the source string for the stream
	ss.str(str);
	//clears any error flags
	ss.clear();
}

/*
 * bool isEmpty - returns true if the stringstream is empty
 */

bool Tokenizer::isEmpty() const
{
	bool status = false;
	//checks if at end of stream (therefore its empty)
	if (ss.eof())
		status = true;

	return status;
}

/*
 * bool readLine - reads the remainder of the stream as a single string
 */

bool Tokenizer::readLine(string& line)
{
	bool status = false;

	if (isEmpty()) //check if stream is empty...
	{
		status = false;
	}
	else if (getline(ss, line)) //if not, try to read a line
	{
		status = true;
	}
	return status;
}

/*
 * bool readInteger - reads an integer value from the stream, otherwise returns false
 */

bool Tokenizer::readInteger(int& val)
{
	bool status = false;
	if (isEmpty()) //check if stream is empty...
	{
		status = false;
	}
	else
	{
		try //try to read val...
		{
			ss >> val;
			status = true;
		}
		catch (std::ios_base::failure) //...otherwise fail and set status
		{
			ss.clear();
			status = false;
		}
	}
	return status;
}

/*
 * bool readWord - reads a single word (as a string) from the stream, otherwise returns false
 */

bool Tokenizer::readWord(string& val)
{
	bool status = false;

	if (isEmpty()) //check if stream is empty...
	{
		status = false;
	}
	else
	{
		try //try to read val...
		{
			ss >> val;
			status = true;
		}
		catch (std::ios_base::failure) //...otherwise fail and set status
		{
			ss.clear();
			status = false;
		}
	}
	return status;
}

/*
 * bool readDouble - reads a double from the stream, otherwise returns false
 */

bool Tokenizer::readDouble(double& val)
{
	bool status = false;
	if (isEmpty()) //check if stream is empty...
	{
		status = false;
	}
	else
	{
		try //try to read val...
		{
			ss >> val;
			status = true;
		}
		catch (std::ios_base::failure) //...otherwise fail and set status
		{
			ss.clear();
			status = false;
		}
	}
	return status;
}

/*
 * bool readChar - reads a single character from the stream, otherwise returns false
 */

bool Tokenizer::readChar(char& val)
{
	bool status = false;
	if (isEmpty()) //check if stream is empty...
	{
		status = false;
	}
	else
	{
		try //try to read val...
		{
			ss >> val;
			status = true;
		}
		catch (std::ios_base::failure) //...otherwise fail and set status
		{
			ss.clear();
			status = false;
		}
	}
	return status;
}

/*
 * void rewind - resets stream to beginning
 */

void Tokenizer::rewind()
{
	ss.seekg(0, ss.beg); //moves stream back to beginning
}

/*
 * void clear - empties the stream
 */

void Tokenizer::clear()
{
	setString(""); //sets stream to empty string
	ss.setstate(std::ios::eofbit); //sets "end of file" flag/state
}