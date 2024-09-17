#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct EisDataPoint
{
	void* priv;
};

double eis_data_point_get_omega(struct EisDataPoint *dp);
double eis_data_point_get_real(struct EisDataPoint *dp);
double eis_data_point_get_imag(struct EisDataPoint *dp);

#ifdef __cplusplus
}
#endif
