#include "kisstype/type.h"
#include <iostream>

int main(int argc, char** argv)
{
	VersionFixed version = eis_get_version();
	std::cout<<"version: "<<version.major<<'.'<<version.minor<<'.'<<version.patch<<'\n';
	return 0;
}
