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

void replace_if_found(std::string& line, std::string what, std::string with)
{
	auto index = line.find(what);
	if (index != std::string::npos)
		line.replace(index, what.size(), with);
}