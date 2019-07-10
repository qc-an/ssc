#include <gtest/gtest.h>

#include "core.h"
#ifndef _CMOD_TCSTROUGH_EMPIRICAL_TEST_H_
#define _CMOD_TCSTROUGH_EMPIRICAL_TEST_H_

#include "../ssc/vartab.h"
#include "../ssc/common.h"
#include "../tcs_test/tcstrough_empirical_cases.h"

/**
 * CMtcsTroughEmpirical tests the cmod_tcstrough_empirical using the SAM code generator to generate data
 * Eventually a method can be written to write this data to a vartable so that lower-level methods of
 * tcstrough_empirical can be tested
 * For now, this uses the SSCAPI interfaces to run the compute module and compare results
 */
class CMtcsTroughEmpirical : public ::testing::Test {

public:

	ssc_data_t data;
	ssc_number_t calculated_value;
	ssc_number_t * calculated_array;
	double m_error_tolerance_hi = 0.01;     // 1.0%
	double m_error_tolerance_lo = 0.001;    // 0.1%

	void SetUp()
	{
		data = ssc_data_create();
		tcstrough_empirical_default(data);
		calculated_array = new ssc_number_t[8760];
	}
	void TearDown() {
		if (data) {
			ssc_data_free(data);
			data = nullptr;
		}
		if (calculated_array) {
			delete[] calculated_array;
		}
	}
	void SetCalculated(std::string name)
	{
		ssc_data_get_number(data, const_cast<char *>(name.c_str()), &calculated_value);
	}
	void SetCalculatedArray(std::string name)
	{
		int n;
		calculated_array = ssc_data_get_array(data, const_cast<char *>(name.c_str()), &n);
	}
};

#endif // !_CMOD_TCSTROUGH_EMPIRICAL_TEST_H
