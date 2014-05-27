template <typename T> 
std::string NumberToString(T Number)
{
    std::stringstream ss;
    ss << Number;
    return ss.str();
}

int StringToInt(std::string s)
{
	std::stringstream ss;
	int i;
	ss << s;
	ss >> i;
	return i;
}