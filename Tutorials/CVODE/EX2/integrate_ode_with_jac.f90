subroutine integrate_ode_with_jac(mf, lo, hi, neq, cvode_meth, cvode_itmeth) bind(C, name="integrate_ode_with_jac")

  use amrex_error_module
  use, intrinsic :: iso_c_binding

  implicit none

  integer(c_int), intent(in) :: lo(3),hi(3)
  integer(c_int), intent(in) :: neq
  real(c_double), intent(inout) :: mf(lo(1):hi(1), lo(2):hi(2), lo(3):hi(3), neq)
  integer(c_int), intent(in) :: cvode_meth
  integer(c_int), intent(in) :: cvode_itmeth

  ! local variables
  integer i,j,k

  integer(c_long) :: neq_long
  integer(c_long) :: ipar(1)
  real(c_double) :: rpar(1)
  integer(c_long) :: iout(21) ! misc integer output parameters generated by CVODE
  real(c_double) :: rout(6) ! misc floating-point output parameters generated by CVODE
  integer :: ier ! CVODE return status
  integer(c_int) :: iatol, itask
  real(c_double) :: t_soln ! final time at the end of CVODE integration
  real(c_double) :: y(neq)
  real(c_double) :: atol(neq), rtol
  real(c_double) :: t0, t1

  neq_long = neq

  ! First arg tells fnvinit() that we are using it for CVODE, not for one of the other solvers in SUNDIALS
  call fnvinits(1, neq_long, ier)
  if (ier /= 0) call amrex_abort("integrate_ode: failed in fnvinits()")

  t0 = 0.0d0 ! initial time for integration
  t1 = 4.0d10 ! final time for integration

  ! Initial conditions
  y(1) = 1.0d0
  y(2) = 0.0d0
  y(3) = 0.0d0

  iatol = 2  ! 1 = scalar atol (1 atol for all eqns); 2 = vector atol (1 atol for each eqn)

  rtol = 1.0d-4
  atol(1) = 1.0d-8
  atol(2) = 1.0d-14
  atol(3) = 1.0d-6

  ipar(1) = 42     ! Pass an arbitrary number of integer parameters into ipar
  rpar(1) = 42.0d0 ! Pass an arbitrary number of floating-point parameters into rpar

  itask = 1 ! 1 = Return from CVODE only after final integration time has been reached
            ! 2 = Return from CVODE after one integration step

  call fcvmalloc(t0, y, cvode_meth, cvode_itmeth, iatol, rtol, atol, iout, rout, ipar, rpar, ier)
  if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvmalloc()")

  call fcvsetiin('MAX_NSTEPS', 10000000, ier)
  if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvsetiin()")

  ! Tell CVODE to use a dense linear solver.
  call fcvdense(neq_long, ier)
  if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvdense()")

  CALL FCVDENSESETJAC(1, IER)
  if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvdensesetjac()")

  do k=lo(3),hi(3)
     do j=lo(2),hi(2)
        do i=lo(1),hi(1)
           ! We will solve the same system of ODEs with the same initial conditions in every cell.
           y(1) = 1.0d0
           y(2) = 0.0d0
           y(3) = 0.0d0
           call fcvreinit(t0, y, iatol, rtol, atol, ier)
           if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvreinit()")
           call fcvode(t1, t_soln, y, itask, ier)
           if (ier /= 0) call amrex_abort("integrate_ode: failed in fcvode()")
           mf(i,j,k,1:neq_long) = y(1:neq_long)
        end do
     end do
  end do

  ! Deallocate memory allocated by fcvmalloc(). Don't know if this also frees the memory created in fnvinit, but the Fortran
  ! interface does not have a corresponding function.
  call fcvfree

end subroutine integrate_ode_with_jac
