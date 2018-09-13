#ifndef __LR_H_
#define __LR_H_

#include "Model.h"

namespace mla {
	namespace lr {
		class LR : public mla::model::Model<int32_t> {

		public:
			int32_t _max_iter_cnt; //����������
			float _learning_rate; //ѧϰ��
			int32_t _thread_cnt; //�߳���
			int32_t _reg_type; //��������
			float _lambda;

			std::vector<float> _w;

			LR() : _reg_type(-1), _lambda(0.0) {} //Ĭ�ϲ�֪������
			virtual ~LR() {}

			//������ʧ����
			float calc_loss_value();

			//����ݶ��½���
			bool stochastic_gradient_descent(std::vector<float> &w,
				float learning_rate,
				const std::vector<std::vector<float> > &feature,
				const std::vector<int32_t> &label,
				float reg_type,
				float lambda);

			//�ݶ��½���
			void gradient_descent(std::vector<float> &w,
				float learning_rate,
				const std::vector<std::vector<float> > &feature,
				const std::vector<int32_t> &label,
				float reg_type,
				float lambda);

			void set_parameter(int32_t max_iter_cnt,
				float learning_rate,
				int32_t reg_type = -1,
				float lambda = 0.0,
				int32_t thread_cnt = 0);

			float sigmoid(float x);
			void train(int32_t opt_type);
			float predict(const std::vector<float> &feature);
			void dump_model(const char* model_file_name);
			void load_model(const char* model_file_name);
		};
	}
}
#endif