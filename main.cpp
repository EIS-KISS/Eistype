#include "kisstype/type.h"
#include "kisstype/spectra.h"
#include <iostream>

int main(int argc, char** argv)
{
	VersionFixed version = eis_get_version();
	std::cout<<"version: "<<version.major<<'.'<<version.minor<<'.'<<version.patch<<'\n';

	if(argc > 1)
	{
		eis::Spectra spectra = eis::Spectra::loadFromDisk(argv[1]);
		std::cout<<spectra<<std::endl;
		std::cout<<"Length: "<<spectra.data.size()<<std::endl;
	}
	return 0;
}
