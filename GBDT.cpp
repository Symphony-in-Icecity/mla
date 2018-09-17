
// gbdt implementation source file

#include "GBDT.h"

namespace mla {

	namespace gbdt {

		// implementation of the functions of regression
		void GradientBoostingRegressionTree::train(int32_t opt_type) {
			if (0 == _feature.size()) {
				std::cerr << "Error Input Training Feature!" << std::endl;
				exit(0);
			}
			int32_t sampleCnt = _label.size();
			int32_t featureDim = _feature.size();

			for (int32_t i = 0; i < sampleCnt; i++) {
				m_vTempGradient.push_back(0.0);
				m_vGradient.push_back(_label[i]);
			}

			for (int32_t i = 0; i < m_nTreeNum; i++) {
				mla::tree::RegressionTree* subTree = new mla::tree::RegressionTree(m_nTreeDepth,
					m_nNodeCnt,
					true);

				subTree->setData(_feature, m_vGradient);
				subTree->train();
				for (int32_t j = 0; j < sampleCnt; j++) {
					float value = subTree->predict(_feature[j]);
					m_vTempGradient[j] += value;
					m_vGradient[j] = _label[j] - m_fLearningRate * m_vTempGradient[j];
				}
				trees.push_back(subTree);
			}
			std::cout << m_nTreeNum << " " << std::endl;
		};

		float GradientBoostingRegressionTree::predict(const std::vector<float> &feature) {
			float value = 0;
			for (int j = 0; j < m_nTreeNum; j++) {
				value += trees[j]->predict(feature);
			}
			return value * m_fLearningRate;
		}

		void GradientBoostingRegressionTree::load_model(const char* model_file_name) {
		}

		void GradientBoostingRegressionTree::dump_model(const char* model_file_name) {
		}

	}

};