#ifndef  __SVM_H_
#define  __SVM_H_

#include "Util.h"
#include "Model.h"

namespace mla {
	namespace svm {
		class SVM : public mla::model::Model<float> {
		private:
			std::vector<int32_t> _support_vec_index;    // ֧��������
			std::vector<int32_t> _bound_vec_index;      // ������߽��ϵĵ�
			std::vector<int32_t> _non_bound_vec_index;  // �߽���ĵ�
			std::vector<float> _alpha;                  // �������ճ���
			std::vector<std::vector<float> > _kernel;   // �˾���
			std::vector<float> _error;                  // ÿ�������ķ������
			float _b;                                   // ƫ��bias 
			float _c;                                   // �кͽṹ���պ;�����յ�ֵ
			int32_t _max_iter_cnt;                      // ����������
		public:
			SVM() {}
			SVM(float C, int32_t max_iter_cnt) :_c(C), _max_iter_cnt(max_iter_cnt) {}
			~SVM() {}
			
			// ��ʼ������ �������ճ���alpha->0.0 �������ֵerror->0.0 ƫ��bias->0.0
			void init_alpha();

			// ���Ե�i�������Ƿ�����kkt����:    
			// 0 < alpha_i < c <=> _y[i] * _error[i] == 0  -> ֧��������
			// 0 == alpha_i    <=> _y[i] * _error[i] > 0   -> �������֮��
			// c == alpha_i    <=> _y[i] * _error[i] < 0   -> �������
			bool fit_kkt(int32_t i);

			// inner loop in standard svm source code
			// so as to find the alpah_j, and update alpha_i, alpha_j, bias, error
			// firstly ,we search the support vectors, if someone in them does'not match
			// the kkt condition, then we choose it as the alpha_i that stays to be optimized
			bool inner_loop(int32_t i);

			// slect alpha_j given alpha_i
			// normally, we search the alpha which can maximum |error_i - error_j| ̰�ķ��������������������
			int32_t select_j(int32_t i);

			// ����֧������
			void update_support_vector_index();

			// update vector index as a result of updating alpha_i & alpha_j
			void  update_bound_vector_index();

			// calculate the kernel output gona to be used in prediction stage
			float kernel_cal(const std::vector<float> &x,
				const std::vector<float> &feature);

			// given the vector values of feature in test sample, output the outcome
			// >= 1: positive <= -1:negative otherwise: unknown
			float predict(const std::vector<float> &feature);

			// train the model
			void train(int32_t opt_type);

			// load the model
			void load_model(const char* model_file_name);

			// dump the model
			void dump_model(const char* model_file_name);
		};

	}
}
#endif
