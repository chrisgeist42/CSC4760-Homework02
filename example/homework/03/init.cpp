#include <Kokkos_Core.hpp>
#include <cstdio>

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View of length n > 1000 and add values
    const int N = 1000;

    Kokkos::View<int*> view1("View1", N);
    Kokkos::parallel_for("InitView1", N, KOKKOS_LAMBDA(const int i) {
        view1(i) = i * i;
    });

    // create two additional views of the same size and datatype
    Kokkos::View<int*> view2("View2", N);
    Kokkos::View<int*> view3("View3", N);

    // deep_copy
    Kokkos::Timer timer_for_deep;
    Kokkos::deep_copy(view2, view1);
    double time_for_deep = timer_for_deep.seconds();

    // user copy
    Kokkos::Timer timer_for_parallel;
    Kokkos::parallel_for("CopyView", N, KOKKOS_LAMBDA(const int i) {
        view3(i) = view1(i);
    });
    double time_for_parallel = timer_for_parallel.seconds();

    // Output times
    printf("Time for deep_copy: %f\n", time_for_deep);
    printf("Time for parallel_for: %f\n", time_for_parallel);
  }
  Kokkos::finalize();
}
