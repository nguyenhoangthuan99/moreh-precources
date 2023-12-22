#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// Naive Matrix Multiplication
// C[MxN] = A[MxK] @ B[KxN]
// Do not remove or modify this definitions 
void matmul_c(float* A, float* B, float* C, int M, int N, int K){

  for (int i = 0 ; i < M ; ++i)
  {
    for (int k = 0 ; k < K ; ++k)
    {
      float tmp = A[i * K + k];
      for (int j = 0 ; j < N ; ++j)
      {
        C[i * N + j] += tmp * B[k * N + j];
      }
    }
  }
}


void matmul_c_interface(py::array_t<float> A, py::array_t<float> B, py::array_t<float> C,int M, int N, int K){
  py::buffer_info A_buf = A.request(), B_buf = B.request(), C_buf = C.request();
  // if (A_buf.ndim != 2 || B_buf.ndim != 2 || C_buf.ndim !=2)
  //       throw std::runtime_error("Number of dimensions must be two");
  // if (A_buf.shape[1] != B_buf.shape[0] || A_buf.shape[0] != C_buf.shape[0] || B_buf.shape[1] != C_buf.shape[1])
  //       throw std::runtime_error("Matrix dimensions do not match for multiplication");
  float *ptr_A = static_cast<float *>(A_buf.ptr);
  float *ptr_B = static_cast<float *>(B_buf.ptr);
  float *ptr_C = static_cast<float *>(C_buf.ptr);

  matmul_c(ptr_A,ptr_B,ptr_C,M,N,K);

  // for (int i = 0 ; i < M ; ++i)
  // {
  //   for (int k = 0 ; k < K ; ++k)
  //   {
  //     float tmp = ptr_A[i * K + k];
  //     for (int j = 0 ; j < N ; ++j)
  //     {
  //       ptr_C[i * N + j] += tmp * ptr_B[k * N + j];
  //     }
  //   }
  // }

}

PYBIND11_MODULE(matmul_c, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("matmul_c_interface", &matmul_c_interface, "A function that adds two numbers");
}

/*


Write your code here



*/
