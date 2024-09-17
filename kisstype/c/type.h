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

struct VersionFixed
{
	int major;
	int minor;
	int patch;
};

const struct VersionFixed eis_get_version();

#ifdef __cplusplus
}
#endif
