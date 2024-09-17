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

}
