#include "c/type.h"
#include "type.h"

extern "C"
{

double eis_data_point_get_omega(struct EisDataPoint *dp)
{
	eis::DataPoint* dataPoint = static_cast<eis::DataPoint*>(dp->priv);
	return dataPoint->omega;
}

double eis_data_point_get_real(struct EisDataPoint *dp)
{
	eis::DataPoint* dataPoint = static_cast<eis::DataPoint*>(dp->priv);
	return dataPoint->im.real();
}

double eis_data_point_get_imag(struct EisDataPoint *dp)
{
	eis::DataPoint* dataPoint = static_cast<eis::DataPoint*>(dp->priv);
	return dataPoint->im.imag();
}

const struct VersionFixed eis_get_version()
{
	return {VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH};
}

}
