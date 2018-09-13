#ifndef __FEATURE_H_
#define __FEATURE_H_

#include "Util.h"

namespace mla {
	namespace feature {
		//��һ��
		void feature_normalize(int32_t normalize_type,
			std::vector<std::vector<float> > &feature);

		void feature_select();

		//kfold����
		void k_fold_validation(int k);

		//������ɢ��
		void feature_discretization(const std::string& dis_primitive_str,
			std::vector<std::vector<float> > &feature);
	}
}
#endif