#ifndef CLSVOF_H
#define CLSVOF_H
#include <cmath>
#include <iostream>
#include "CompKernel.h"
#include "ModelFactory.h"

// True characteristic functions
#define heaviside(z) (z>0 ? 1. : (z<0 ? 0. : 0.5))
#define sign(z) (z>0 ? 1. : (z<0 ? -1. : 0.))

namespace proteus
{
  class CLSVOF_base
  {
    //The base class defining the interface
  public:
    virtual ~CLSVOF_base(){}
    virtual void calculateResidual(//element
                                   double dt,
                                   double* mesh_trial_ref,
                                   double* mesh_grad_trial_ref,
                                   double* mesh_dof,
                                   double* mesh_velocity_dof,
                                   double MOVING_DOMAIN,
                                   int* mesh_l2g,
                                   double* dV_ref,
                                   double* u_trial_ref,
                                   double* u_grad_trial_ref,
                                   double* u_test_ref,
                                   double* u_grad_test_ref,
                                   //element boundary
                                   double* mesh_trial_trace_ref,
                                   double* mesh_grad_trial_trace_ref,
                                   double* dS_ref,
                                   double* u_trial_trace_ref,
                                   double* u_grad_trial_trace_ref,
                                   double* u_test_trace_ref,
                                   double* u_grad_test_trace_ref,
                                   double* normal_ref,
                                   double* boundaryJac_ref,
                                   //physics
                                   int nElements_global,
                                   double useMetrics,
                                   double alphaBDF,
                                   //VRANS
                                   const double* q_porosity,
                                   const double* porosity_dof, /////
                                   //
                                   int* u_l2g,
                                   double* elementDiameter,
                                   double* nodeDiametersArray,
                                   int degree_polynomial,
                                   double* u_dof,
                                   double* u_dof_old,
                                   double* velocity,
                                   double* velocity_old,
                                   double* q_m,
                                   double* q_u,
                                   double* q_m_betaBDF,
                                   double* q_dV,
                                   double* q_dV_last,
                                   double* cfl,
                                   int offset_u, int stride_u,
                                   double* globalResidual,
                                   int nExteriorElementBoundaries_global,
                                   int* exteriorElementBoundariesArray,
                                   int* elementBoundaryElementsArray,
                                   int* elementBoundaryLocalElementBoundariesArray,
                                   double* ebqe_velocity_ext,
                                   //VRANS
                                   const double* ebqe_porosity_ext,
                                   //
                                   int* isDOFBoundary_u,
                                   double* ebqe_bc_u_ext,
                                   int* isFluxBoundary_u,
                                   double* ebqe_bc_flux_u_ext,
                                   double* ebqe_u,
                                   double* ebqe_flux,
                                   // FOR NONLINEAR CLSVOF; i.e., MCorr with VOF
                                   int timeOrder,
                                   int timeStage,
                                   double epsFactHeaviside,
                                   double epsFactDirac,
                                   double lambdaFact,
                                   // normalization factor
                                   double* norm_factor,
                                   double norm_factor_lagged,
                                   // normal reconstruction
                                   double* lumped_qx,
                                   double* lumped_qy,
                                   double* lumped_qz,
                                   double* lumped_qx_tStar,
                                   double* lumped_qy_tStar,
                                   double* lumped_qz_tStar,
                                   // AUX QUANTITIES OF INTEREST
                                   double* quantDOFs)=0;
    virtual void calculateJacobian(//element
                                   double dt,
                                   double* mesh_trial_ref,
                                   double* mesh_grad_trial_ref,
                                   double* mesh_dof,
                                   double* mesh_velocity_dof,
                                   double MOVING_DOMAIN,
                                   int* mesh_l2g,
                                   double* dV_ref,
                                   double* u_trial_ref,
                                   double* u_grad_trial_ref,
                                   double* u_test_ref,
                                   double* u_grad_test_ref,
                                   //element boundary
                                   double* mesh_trial_trace_ref,
                                   double* mesh_grad_trial_trace_ref,
                                   double* dS_ref,
                                   double* u_trial_trace_ref,
                                   double* u_grad_trial_trace_ref,
                                   double* u_test_trace_ref,
                                   double* u_grad_test_trace_ref,
                                   double* normal_ref,
                                   double* boundaryJac_ref,
                                   //physics
                                   int nElements_global,
                                   double useMetrics,
                                   double alphaBDF,
                                   //VRANS
                                   const double* q_porosity,
                                   //
                                   int* u_l2g,
                                   double* elementDiameter,
                                   double* nodeDiametersArray,
                                   int degree_polynomial,
                                   double* u_dof,
                                   double* u_dof_old,
                                   double* velocity,
                                   double* q_m_betaBDF,
                                   double* cfl,
                                   int* csrRowIndeces_u_u,int* csrColumnOffsets_u_u,
                                   double* globalJacobian,
                                   int nExteriorElementBoundaries_global,
                                   int* exteriorElementBoundariesArray,
                                   int* elementBoundaryElementsArray,
                                   int* elementBoundaryLocalElementBoundariesArray,
                                   double* ebqe_velocity_ext,
                                   //VRANS
                                   const double* ebqe_porosity_ext,
                                   //
                                   int* isDOFBoundary_u,
                                   double* ebqe_bc_u_ext,
                                   int* isFluxBoundary_u,
                                   double* ebqe_bc_flux_u_ext,
                                   int* csrColumnOffsets_eb_u_u,
                                   // FOR NONLINEAR CLSVOF; i.e., MCorr with VOF
                                   int timeOrder,
                                   int timeStage,
                                   double epsFactHeaviside,
                                   double epsFactDirac,
                                   double lambdaFact,
                                   // normalization factor
                                   double norm_factor_lagged,
                                   // normal reconstruction
                                   double* lumped_qx,
                                   double* lumped_qy,
                                   double* lumped_qz,
                                   double* lumped_qx_tStar,
                                   double* lumped_qy_tStar,
                                   double* lumped_qz_tStar
                                   )=0;
    virtual void calculateMetricsAtEOS( //EOS=End Of Simulation
                                       double* mesh_trial_ref,
                                       double* mesh_grad_trial_ref,
                                       double* mesh_dof,
                                       int* mesh_l2g,
                                       double* dV_ref,
                                       double* u_trial_ref,
                                       double* u_grad_trial_ref,
                                       double* u_test_ref,
                                       //physics
                                       int nElements_global,
                                       int useMetrics,
                                       int* u_l2g,
                                       double* elementDiameter,
                                       double* nodeDiametersArray,
                                       double degree_polynomial,
                                       double epsFactHeaviside,
                                       double* u_dof,
                                       double* u0_dof,
                                       double* u_exact,
                                       int offset_u, int stride_u,
                                       double* global_I_err,
                                       double* global_Ieps_err,
                                       double* global_V_err,
                                       double* global_Veps_err,
                                       double* global_D_err)=0;
    virtual void calculateMetricsAtETS( //ETS=Every Time Step
                                       double dt,
                                       double* mesh_trial_ref,
                                       double* mesh_grad_trial_ref,
                                       double* mesh_dof,
                                       int* mesh_l2g,
                                       double* dV_ref,
                                       double* u_trial_ref,
                                       double* u_grad_trial_ref,
                                       double* u_test_ref,
                                       //physics
                                       int nElements_global,
                                       int useMetrics,
                                       int* u_l2g,
                                       double* elementDiameter,
                                       double* nodeDiametersArray,
                                       double degree_polynomial,
                                       double epsFactHeaviside,
                                       double* u_dof,
                                       double* u_dof_old,
                                       double* u0_dof,
                                       double* velocity,
                                       int offset_u, int stride_u,
                                       int numDOFs,
                                       double* global_R,
                                       double* global_Reps,
                                       double* global_V_err,
                                       double* global_Veps_err,
                                       double* global_D_err)=0;
    virtual void normalReconstruction(double* mesh_trial_ref,
                                      double* mesh_grad_trial_ref,
                                      double* mesh_dof,
                                      int* mesh_l2g,
                                      double* dV_ref,
                                      double* u_trial_ref,
                                      double* u_grad_trial_ref,
                                      double* u_test_ref,
                                      int nElements_global,
                                      int* u_l2g,
                                      double* elementDiameter,
                                      double* u_dof,
                                      int offset_u, int stride_u,
                                      int numDOFs,
                                      double* lumped_qx,
                                      double* lumped_qy,
                                      double* lumped_qz)=0;
  };

  template<class CompKernelType,
    int nSpace,
    int nQuadraturePoints_element,
    int nDOF_mesh_trial_element,
    int nDOF_trial_element,
    int nDOF_test_element,
    int nQuadraturePoints_elementBoundary>
    class CLSVOF : public CLSVOF_base
    {
    public:
      const int nDOF_test_X_trial_element;
      CompKernelType ck;
    CLSVOF():
      nDOF_test_X_trial_element(nDOF_test_element*nDOF_trial_element),
        ck()
          {}
      
      inline
        void calculateCFL(const double& elementDiameter,
                          const double df[nSpace],
                          double& cfl)
      {
        double h,nrm_v;
        h = elementDiameter;
        nrm_v=0.0;
        for(int I=0;I<nSpace;I++)
          nrm_v+=df[I]*df[I];
        nrm_v = sqrt(nrm_v);
        cfl = nrm_v/h;
      }

      inline
        void exteriorNumericalAdvectiveFlux(const int& isDOFBoundary_u,
                                            const int& isFluxBoundary_u,
                                            const double n[nSpace],
                                            const double& bc_u,
                                            const double& bc_flux_u,
                                            const double& u,
                                            const double velocity[nSpace],
                                            double& flux)
      {
        double flow=0.0;
        for (int I=0; I < nSpace; I++)
          flow += n[I]*velocity[I];
        if (isDOFBoundary_u == 1)
          {
            if (flow >= 0.0)
              {
                flux = u*flow;
              }
            else
              {
                flux = bc_u*flow;
              }
          }
        else if (isFluxBoundary_u == 1)
          {
            flux = bc_flux_u;
          }
        else
          {
            if (flow >= 0.0)
              {
                flux = u*flow;
              }
            else
              {
                std::cout<<"warning: CLSVOF open boundary with no external trace, setting to zero for inflow"<<std::endl;
                flux = 0.0;
              }

          }
      }

      inline double smoothedHeaviside(double eps, double u)
      {
        double H;
        if (u > eps)
          H=1.0;
        else if (u < -eps)
          H=0.0;
        else if (u==0.0)
          H=0.5;
        else
          H = 0.5*(1.0 + u/eps + sin(M_PI*u/eps)/M_PI);
        return H;
      }

      inline double smoothedDirac(double eps, double u)
      {
        double d;
        if (u > eps)
          d=0.0;
        else if (u < -eps)
          d=0.0;
        else
          d = 0.5*(1.0 + cos(M_PI*u/eps))/eps;
        return d;
      }

      inline double smoothedSign(double eps, double u)
      {
        double H;
        if (u > eps)
          H=1.0;
        else if (u < -eps)
          H=0.0;
        else if (u==0.0)
          H=0.5;
        else
          H = 0.5*(1.0 + u/eps + sin(M_PI*u/eps)/M_PI);
        return 2*H-1;
      }

      inline double smoothedDerivativeSign(double eps, double u)
      {
        double d;
        if (u > eps)
          d=0.0;
        else if (u < -eps)
          d=0.0;
        else
          d = 0.5*(1.0 + cos(M_PI*u/eps))/eps;
        return 2*d;
      }

      void calculateResidual(//element
                             double dt,
                             double* mesh_trial_ref,
                             double* mesh_grad_trial_ref,
                             double* mesh_dof,
                             double* mesh_velocity_dof,
                             double MOVING_DOMAIN,
                             int* mesh_l2g,
                             double* dV_ref,
                             double* u_trial_ref,
                             double* u_grad_trial_ref,
                             double* u_test_ref,
                             double* u_grad_test_ref,
                             //element boundary
                             double* mesh_trial_trace_ref,
                             double* mesh_grad_trial_trace_ref,
                             double* dS_ref,
                             double* u_trial_trace_ref,
                             double* u_grad_trial_trace_ref,
                             double* u_test_trace_ref,
                             double* u_grad_test_trace_ref,
                             double* normal_ref,
                             double* boundaryJac_ref,
                             //physics
                             int nElements_global,
                             double useMetrics,
                             double alphaBDF,
                             //VRANS
                             const double* q_porosity,
                             const double* porosity_dof,
                             //
                             int* u_l2g,
                             double* elementDiameter,
                             double* nodeDiametersArray,
                             int degree_polynomial,
                             double* u_dof,
                             double* u_dof_old,
                             double* velocity,
                             double* velocity_old,
                             double* q_m,
                             double* q_u,
                             double* q_m_betaBDF,
                             double* q_dV,
                             double* q_dV_last,
                             double* cfl,
                             int offset_u, int stride_u,
                             double* globalResidual,
                             int nExteriorElementBoundaries_global,
                             int* exteriorElementBoundariesArray,
                             int* elementBoundaryElementsArray,
                             int* elementBoundaryLocalElementBoundariesArray,
                             double* ebqe_velocity_ext,
                             //VRANS
                             const double* ebqe_porosity_ext,
                             //
                             int* isDOFBoundary_u,
                             double* ebqe_bc_u_ext,
                             int* isFluxBoundary_u,
                             double* ebqe_bc_flux_u_ext,
                             double* ebqe_u,
                             double* ebqe_flux,
                             // FOR NONLINEAR CLSVOF; i.e., MCorr with VOF
                             int timeOrder,
                             int timeStage,
                             double epsFactHeaviside,
                             double epsFactDirac,
                             double lambdaFact,
                             // normalization factor
                             double* norm_factor,
                             double norm_factor_lagged,
                             // normal reconstruction
                             double* lumped_qx,
                             double* lumped_qy,
                             double* lumped_qz,
                             double* lumped_qx_tStar,
                             double* lumped_qy_tStar,
                             double* lumped_qz_tStar,
                             // AUX QUANTITIES OF INTEREST
                             double* quantDOFs)
      {
        double min_distance = 1E10;
        double max_distance = -1E10;
        double mean_distance = 0.;

        for(int eN=0;eN<nElements_global;eN++)
          {
            //declare local storage for local contributions and initialize
            register double elementResidual_u[nDOF_test_element];
            for (int i=0;i<nDOF_test_element;i++)
              elementResidual_u[i]=0.0;
            //loop over quadrature points and compute integrands
            for  (int k=0;k<nQuadraturePoints_element;k++)
              {
                //compute indeces and declare local storage
                register int eN_k = eN*nQuadraturePoints_element+k,
                  eN_k_nSpace = eN_k*nSpace,
                  eN_nDOF_trial_element = eN*nDOF_trial_element;
                register double
                  //for mass matrix contributions
                  u, un, grad_u[nSpace], grad_un[nSpace], grad_unHalf[nSpace],
                  normalReconstruction[3], // assume 3D always
                  qxn, qyn, qzn, qxnStar, qynStar, qznStar,
                  relative_velocity[nSpace], relative_velocity_old[nSpace],
                  fnp1[nSpace], fnHalf[nSpace], //f=velocity*H(phi)
                  u_test_dV[nDOF_trial_element],
                  u_grad_trial[nDOF_trial_element*nSpace],
                  u_grad_test_dV[nDOF_test_element*nSpace],
                  //for general use
                  jac[nSpace*nSpace], jacDet, jacInv[nSpace*nSpace],
                  dV,x,y,z,xt,yt,zt,h_phi;
                //get the physical integration weight
                ck.calculateMapping_element(eN,
                                            k,
                                            mesh_dof,
                                            mesh_l2g,
                                            mesh_trial_ref,
                                            mesh_grad_trial_ref,
                                            jac,
                                            jacDet,
                                            jacInv,
                                            x,y,z);
                ck.calculateH_element(eN,
                                      k,
                                      nodeDiametersArray,
                                      mesh_l2g,
                                      mesh_trial_ref,
                                      h_phi);
                ck.calculateMappingVelocity_element(eN,
                                                    k,
                                                    mesh_velocity_dof,
                                                    mesh_l2g,
                                                    mesh_trial_ref,
                                                    xt,yt,zt);
                dV = fabs(jacDet)*dV_ref[k];
                ck.gradTrialFromRef(&u_grad_trial_ref[k*nDOF_trial_element*nSpace],jacInv,u_grad_trial);
                // get the components of the normal reconstruction
                ck.valFromDOF(lumped_qx,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qxn);
                ck.valFromDOF(lumped_qy,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qyn);
                ck.valFromDOF(lumped_qz,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qzn);
                ck.valFromDOF(lumped_qx_tStar,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qxnStar);
                ck.valFromDOF(lumped_qy_tStar,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qynStar);
                ck.valFromDOF(lumped_qz_tStar,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],qznStar);
                // get the solution (of Newton's solver)
                ck.valFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],u);
                // get old solution
                ck.valFromDOF(u_dof_old,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],un);
                //get the solution gradients at quad points
                ck.gradFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],u_grad_trial,grad_u);
                ck.gradFromDOF(u_dof_old,&u_l2g[eN_nDOF_trial_element],u_grad_trial,grad_un);
                //precalculate test function products with integration weights for mass matrix terms
                for (int j=0;j<nDOF_trial_element;j++)
                  {
                    u_test_dV[j] = u_test_ref[k*nDOF_trial_element+j]*dV;
                    for (int I=0;I<nSpace;I++)
                      u_grad_test_dV[j*nSpace+I] = u_grad_trial[j*nSpace+I]*dV;
                  }
                //calculate time derivative at quadrature points
                if (q_dV_last[eN_k] <= -100)
                  q_dV_last[eN_k] = dV;
                q_dV[eN_k] = dV;
                /////////////////
                // MOVING MESH //
                /////////////////
                double mesh_velocity[3];
                mesh_velocity[0] = xt;
                mesh_velocity[1] = yt;
                mesh_velocity[2] = zt;

                double lambda = lambdaFact*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial/norm_factor_lagged;
                double epsHeaviside = epsFactHeaviside*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial;
                double Hn = smoothedSign(epsHeaviside,un);
                double Hnp1 = smoothedSign(epsHeaviside,u);

                for (int I=0;I<nSpace;I++)
                  {
                    relative_velocity[I] = (velocity[eN_k_nSpace+I]-MOVING_DOMAIN*mesh_velocity[I]);
                    relative_velocity_old[I] = (velocity_old[eN_k_nSpace+I]-MOVING_DOMAIN*mesh_velocity[I]);
                    fnp1[I] = relative_velocity[I]*Hnp1; //implicit advection via BDF
                    fnHalf[I] = 0.5*(relative_velocity[I]*Hnp1+relative_velocity_old[I]*Hn); //implicit advection via CN
                    grad_unHalf[I] = 0.5*(grad_u[I]+grad_un[I]);
                  }

                //////////////////////////////
                // CALCULATE CELL BASED CFL //
                //////////////////////////////
                calculateCFL(elementDiameter[eN]/degree_polynomial,relative_velocity,cfl[eN_k]);

                /////////////////////
                // TIME DERIVATIVE //
                /////////////////////
                double time_derivative_residual = (Hnp1-Hn)/dt;

                // CALCULATE min, max and mean distance
                min_distance = fmin(min_distance,u);
                max_distance = fmax(max_distance,u);
                mean_distance += u*dV;

                ///////////////////////////
                // NORMAL RECONSTRUCTION //
                ///////////////////////////
                if (timeOrder == 2 && timeStage == 2)
                  {
                    normalReconstruction[0] = 0.5*(qxnStar+qxn);
                    normalReconstruction[1] = 0.5*(qynStar+qyn);
                    if (nSpace==3)
                      normalReconstruction[2] = 0.5*(qznStar+qzn);
                    else
                      normalReconstruction[2] = 0.;
                  }
                else //timeOrder == 1 or timeStage==1
                  {
                    normalReconstruction[0] = qxn;
                    normalReconstruction[1] = qyn;
                    if (nSpace==3)
                      normalReconstruction[2] = qzn;
                    else
                      normalReconstruction[2] = 0.;
                  }
                //////////////////
                // LOOP ON DOFs //
                //////////////////
                for(int i=0;i<nDOF_test_element;i++)
                  {
                    register int i_nSpace=i*nSpace;
                    if (timeOrder==1)
                      {
                        elementResidual_u[i] +=
                          // TIME DERIVATIVE
                          time_derivative_residual*u_test_dV[i]
                          // ADVECTION TERM. This is IMPLICIT
                          + ck.Advection_weak(fnp1,&u_grad_test_dV[i_nSpace])
                          // REGULARIZATION TERM. This is IMPLICIT
                          + lambda*ck.NumericalDiffusion(1.0,
                                                         grad_u,
                                                         &u_grad_test_dV[i_nSpace])
                          // TARGET for PENALIZATION. This is EXPLICIT
                          - lambda*ck.NumericalDiffusion(1.0,
                                                         normalReconstruction,
                                                         &u_grad_test_dV[i_nSpace]);
                      }
                    else // timeOrder=2
                      elementResidual_u[i] +=
                        // TIME DERIVATIVE
                        time_derivative_residual*u_test_dV[i]
                        // ADVECTION TERM. This is IMPLICIT
                        + ck.Advection_weak(fnHalf,&u_grad_test_dV[i_nSpace])
                        // REGULARIZATION TERM. This is IMPLICIT
                        + lambda*ck.NumericalDiffusion(1.0,
                                                       grad_unHalf,
                                                       &u_grad_test_dV[i_nSpace])
                        // TARGET for PENALIZATION. This is EXPLICIT
                        - lambda*ck.NumericalDiffusion(1.0,
                                                       normalReconstruction,
                                                       &u_grad_test_dV[i_nSpace]);
                  }//i
                //save solution for other models
                q_u[eN_k] = u;
                q_m[eN_k] = u;//porosity*u;
              }
            /////////////////
            // DISTRIBUTE // load cell based element into global residual
            ////////////////
            for(int i=0;i<nDOF_test_element;i++)
              {
                int eN_i=eN*nDOF_test_element+i;
                int gi = offset_u+stride_u*u_l2g[eN_i]; //global i-th index
                // distribute global residual for (lumped) mass matrix
                globalResidual[gi] += elementResidual_u[i];
              }//i
          }//elements
        // COMPUTE NORMALIZATION FACTOR
        norm_factor[0] = fmax(fabs(max_distance - mean_distance),
                              fabs(mean_distance - min_distance));

        //////////////
        // BOUNDARY //
        //////////////
        //ebNE is the Exterior element boundary INdex
        //ebN is the element boundary INdex
        //eN is the element index
        for (int ebNE = 0; ebNE < nExteriorElementBoundaries_global; ebNE++)
          {
            register int ebN = exteriorElementBoundariesArray[ebNE],
              eN  = elementBoundaryElementsArray[ebN*2+0],
              ebN_local = elementBoundaryLocalElementBoundariesArray[ebN*2+0],
              eN_nDOF_trial_element = eN*nDOF_trial_element;
            register double elementResidual_u[nDOF_test_element];
            for (int i=0;i<nDOF_test_element;i++)
              {
                elementResidual_u[i]=0.0;
              }
            for  (int kb=0;kb<nQuadraturePoints_elementBoundary;kb++)
              {
                register int ebNE_kb = ebNE*nQuadraturePoints_elementBoundary+kb,
                  ebNE_kb_nSpace = ebNE_kb*nSpace,
                  ebN_local_kb = ebN_local*nQuadraturePoints_elementBoundary+kb,
                  ebN_local_kb_nSpace = ebN_local_kb*nSpace;
                register double
                  u_ext=0.0,
                  df_ext[nSpace],
                  flux_ext=0.0,
                  bc_u_ext=0.0,
                  jac_ext[nSpace*nSpace],
                  jacDet_ext,
                  jacInv_ext[nSpace*nSpace],
                  boundaryJac[nSpace*(nSpace-1)],
                  metricTensor[(nSpace-1)*(nSpace-1)],
                  metricTensorDetSqrt,
                  dS,
                  u_test_dS[nDOF_test_element],
                  normal[nSpace],x_ext,y_ext,z_ext,xt_ext,yt_ext,zt_ext,integralScaling,
                  //VRANS
                  porosity_ext;
                //
                //calculate the solution and gradients at quadrature points
                //
                //compute information about mapping from reference element to physical element
                ck.calculateMapping_elementBoundary(eN,
                                                    ebN_local,
                                                    kb,
                                                    ebN_local_kb,
                                                    mesh_dof,
                                                    mesh_l2g,
                                                    mesh_trial_trace_ref,
                                                    mesh_grad_trial_trace_ref,
                                                    boundaryJac_ref,
                                                    jac_ext,
                                                    jacDet_ext,
                                                    jacInv_ext,
                                                    boundaryJac,
                                                    metricTensor,
                                                    metricTensorDetSqrt,
                                                    normal_ref,
                                                    normal,
                                                    x_ext,y_ext,z_ext);
                ck.calculateMappingVelocity_elementBoundary(eN,
                                                            ebN_local,
                                                            kb,
                                                            ebN_local_kb,
                                                            mesh_velocity_dof,
                                                            mesh_l2g,
                                                            mesh_trial_trace_ref,
                                                            xt_ext,yt_ext,zt_ext,
                                                            normal,
                                                            boundaryJac,
                                                            metricTensor,
                                                            integralScaling);
                dS = ((1.0-MOVING_DOMAIN)*metricTensorDetSqrt + MOVING_DOMAIN*integralScaling)*dS_ref[kb];
                //solution at quad points
                ck.valFromDOF(u_dof_old,&u_l2g[eN_nDOF_trial_element],&u_trial_trace_ref[ebN_local_kb*nDOF_test_element],u_ext);
                //precalculate test function products with integration weights
                for (int j=0;j<nDOF_trial_element;j++)
                  u_test_dS[j] = u_test_trace_ref[ebN_local_kb*nDOF_test_element+j]*dS;
                //
                //load the boundary values
                //
                bc_u_ext = isDOFBoundary_u[ebNE_kb]*ebqe_bc_u_ext[ebNE_kb]+(1-isDOFBoundary_u[ebNE_kb])*u_ext;
                //VRANS
                porosity_ext = ebqe_porosity_ext[ebNE_kb];
                //
                //moving mesh
                //
                double mesh_velocity[3];
                mesh_velocity[0] = xt_ext;
                mesh_velocity[1] = yt_ext;
                mesh_velocity[2] = zt_ext;
                for (int I=0;I<nSpace;I++)
                  df_ext[I] = porosity_ext*(ebqe_velocity_ext[ebNE_kb_nSpace+I] -
                                            MOVING_DOMAIN*mesh_velocity[I]);
                //
                //calculate the numerical fluxes
                //
                double epsHeaviside = epsFactHeaviside*elementDiameter[eN]/degree_polynomial;
                double sHu_ext = smoothedSign(epsHeaviside,u_ext);
                exteriorNumericalAdvectiveFlux(isDOFBoundary_u[ebNE_kb],
                                               isFluxBoundary_u[ebNE_kb],
                                               normal,
                                               bc_u_ext, //1 or -1
                                               ebqe_bc_flux_u_ext[ebNE_kb],
                                               sHu_ext, //Sign(u_ext)
                                               df_ext, //VRANS includes porosity
                                               flux_ext);
                ebqe_flux[ebNE_kb] = flux_ext;
                //save for other models? cek need to be consistent with numerical flux
                if(flux_ext >=0.0)
                  ebqe_u[ebNE_kb] = u_ext;
                else
                  ebqe_u[ebNE_kb] = bc_u_ext;
                //
                //update residuals
                //
                for (int i=0;i<nDOF_test_element;i++)
                  {
                    elementResidual_u[i] += ck.ExteriorElementBoundaryFlux(flux_ext,u_test_dS[i]);
                  }//i
              }//kb
            //
            //update the element and global residual storage
            //
            for (int i=0;i<nDOF_test_element;i++)
              {
                int eN_i = eN*nDOF_test_element+i;
                globalResidual[offset_u+stride_u*u_l2g[eN_i]] += elementResidual_u[i];
              }//i
          }//ebNE
        // END OF BOUNDARY //
      }

      void calculateJacobian(//element
                             double dt,
                             double* mesh_trial_ref,
                             double* mesh_grad_trial_ref,
                             double* mesh_dof,
                             double* mesh_velocity_dof,
                             double MOVING_DOMAIN,
                             int* mesh_l2g,
                             double* dV_ref,
                             double* u_trial_ref,
                             double* u_grad_trial_ref,
                             double* u_test_ref,
                             double* u_grad_test_ref,
                             //element boundary
                             double* mesh_trial_trace_ref,
                             double* mesh_grad_trial_trace_ref,
                             double* dS_ref,
                             double* u_trial_trace_ref,
                             double* u_grad_trial_trace_ref,
                             double* u_test_trace_ref,
                             double* u_grad_test_trace_ref,
                             double* normal_ref,
                             double* boundaryJac_ref,
                             //physics
                             int nElements_global,
                             double useMetrics,
                             double alphaBDF,
                             //VRANS
                             const double* q_porosity,
                             //
                             int* u_l2g,
                             double* elementDiameter,
                             double* nodeDiametersArray,
                             int degree_polynomial,
                             double* u_dof,
                             double* u_dof_old,
                             double* velocity,
                             double* q_m_betaBDF,
                             double* cfl,
                             int* csrRowIndeces_u_u,int* csrColumnOffsets_u_u,
                             double* globalJacobian,
                             int nExteriorElementBoundaries_global,
                             int* exteriorElementBoundariesArray,
                             int* elementBoundaryElementsArray,
                             int* elementBoundaryLocalElementBoundariesArray,
                             double* ebqe_velocity_ext,
                             //VRANS
                             const double* ebqe_porosity_ext,
                             //
                             int* isDOFBoundary_u,
                             double* ebqe_bc_u_ext,
                             int* isFluxBoundary_u,
                             double* ebqe_bc_flux_u_ext,
                             int* csrColumnOffsets_eb_u_u,
                             // FOR NONLINEAR CLSVOF; i.e., MCorr with VOF
                             int timeOrder,
                             int timeStage,
                             double epsFactHeaviside,
                             double epsFactDirac,
                             double lambdaFact,
                             // normalization factor
                             double norm_factor_lagged,
                             // normal reconstruction
                             double* lumped_qx,
                             double* lumped_qy,
                             double* lumped_qz,
                             double* lumped_qx_tStar,
                             double* lumped_qy_tStar,
                             double* lumped_qz_tStar)
      {
        double timeCoeff=1.0;
        if (timeOrder==2)
          timeCoeff=0.5;
        for(int eN=0;eN<nElements_global;eN++)
          {
            register double  elementJacobian_u_u[nDOF_test_element][nDOF_trial_element];
            for (int i=0;i<nDOF_test_element;i++)
              for (int j=0;j<nDOF_trial_element;j++)
                elementJacobian_u_u[i][j]=0.0;
            for  (int k=0;k<nQuadraturePoints_element;k++)
              {
                int eN_k = eN*nQuadraturePoints_element+k, //index to a scalar at a quadrature point
                  eN_k_nSpace = eN_k*nSpace,
                  eN_nDOF_trial_element = eN*nDOF_trial_element; //index to a vector at a quadrature point
                //declare local storage
                register double
                  u, un, u_grad_trial[nDOF_trial_element*nSpace],
                  relative_velocity[nSpace], df[nSpace],
                  jac[nSpace*nSpace], jacDet, jacInv[nSpace*nSpace],
                  u_test_dV[nDOF_test_element], u_grad_test_dV[nDOF_test_element*nSpace],
                  dV, x,y,z,xt,yt,zt,h_phi;
                //get jacobian, etc for mapping reference element
                ck.calculateMapping_element(eN,
                                            k,
                                            mesh_dof,
                                            mesh_l2g,
                                            mesh_trial_ref,
                                            mesh_grad_trial_ref,
                                            jac,
                                            jacDet,
                                            jacInv,
                                            x,y,z);
                ck.calculateH_element(eN,
                                      k,
                                      nodeDiametersArray,
                                      mesh_l2g,
                                      mesh_trial_ref,
                                      h_phi);
                ck.calculateMappingVelocity_element(eN,
                                                    k,
                                                    mesh_velocity_dof,
                                                    mesh_l2g,
                                                    mesh_trial_ref,
                                                    xt,yt,zt);
                //get the physical integration weight
                dV = fabs(jacDet)*dV_ref[k];
                //get the trial function gradients
                ck.gradTrialFromRef(&u_grad_trial_ref[k*nDOF_trial_element*nSpace],jacInv,u_grad_trial);
                //get the solution
                ck.valFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],u);
                ck.valFromDOF(u_dof_old,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],un);
                //precalculate test function products with integration weights
                for (int j=0;j<nDOF_trial_element;j++)
                  {
                    u_test_dV[j] = u_test_ref[k*nDOF_trial_element+j]*dV;
                    for (int I=0;I<nSpace;I++)
                      u_grad_test_dV[j*nSpace+I]   = u_grad_trial[j*nSpace+I]*dV;
                  }

                /////////////////
                // MOVING MESH //
                /////////////////
                double mesh_velocity[3];
                mesh_velocity[0] = xt;
                mesh_velocity[1] = yt;
                mesh_velocity[2] = zt;

                double lambda = lambdaFact*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial/norm_factor_lagged;
                double epsDirac = epsFactDirac*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial;
                double epsHeaviside = epsFactHeaviside*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial;
                double dHnp1 = smoothedDerivativeSign(epsDirac,u); //derivative of smoothed sign

                for (int I=0;I<nSpace;I++)
                  {
                    relative_velocity[I] = (velocity[eN_k_nSpace+I]-MOVING_DOMAIN*mesh_velocity[I]);
                    df[I] = relative_velocity[I]*dHnp1;
                  }

                /////////////////////
                // TIME DERIVATIVE //
                /////////////////////
                double time_derivative_jacobian = dHnp1/dt;

                //////////////////
                // LOOP ON DOFs //
                //////////////////
                for(int i=0;i<nDOF_test_element;i++)
                  {
                    for(int j=0;j<nDOF_trial_element;j++)
                      {
                        int j_nSpace = j*nSpace;
                        int i_nSpace = i*nSpace;

                        elementJacobian_u_u[i][j] +=
                          // TIME DERIVATIVE
                          time_derivative_jacobian*u_trial_ref[k*nDOF_trial_element+j]*u_test_dV[i]
                          // IMPLICIT TERMS: ADVECTION, DIFFUSION
                          + timeCoeff*
                          (ck.AdvectionJacobian_weak(df,
                                                     u_trial_ref[k*nDOF_trial_element+j],
                                                     &u_grad_test_dV[i_nSpace])
                           + lambda*ck.NumericalDiffusionJacobian(1.0,
                                                                  &u_grad_trial[j_nSpace],
                                                                  &u_grad_test_dV[i_nSpace]));
                      }//j
                  }//i
              }//k
            //
            //load into element Jacobian into global Jacobian
            //
            for (int i=0;i<nDOF_test_element;i++)
              {
                int eN_i = eN*nDOF_test_element+i;
                for (int j=0;j<nDOF_trial_element;j++)
                  {
                    int eN_i_j = eN_i*nDOF_trial_element+j;
                    globalJacobian[csrRowIndeces_u_u[eN_i] + csrColumnOffsets_u_u[eN_i_j]] +=
                      elementJacobian_u_u[i][j];
                  }//j
              }//i
          }//elements

        ///////////////////
        // BOUNDARY LOOP //
        ///////////////////
        // No need since I impose the boundary explicitly
      }//computeJacobian for MCorr with CLSVOF

      void calculateMetricsAtEOS( //EOS=End Of Simulation
                                 double* mesh_trial_ref,
                                 double* mesh_grad_trial_ref,
                                 double* mesh_dof,
                                 int* mesh_l2g,
                                 double* dV_ref,
                                 double* u_trial_ref,
                                 double* u_grad_trial_ref,
                                 double* u_test_ref,
                                 //physics
                                 int nElements_global,
                                 int useMetrics,
                                 int* u_l2g,
                                 double* elementDiameter,
                                 double* nodeDiametersArray,
                                 double degree_polynomial,
                                 double epsFactHeaviside,
                                 double* u_dof,
                                 double* u0_dof,
                                 double* u_exact,
                                 int offset_u, int stride_u,
                                 double* global_I_err,
                                 double* global_Ieps_err,
                                 double* global_V_err,
                                 double* global_Veps_err,
                                 double* global_D_err)
      {
        double global_V = 0.;
        double global_V0 = 0.;
        double global_sV = 0.;
        double global_sV0 = 0.;
        *global_I_err = 0.0;
        *global_Ieps_err = 0.0;
        *global_V_err = 0.0;
        *global_Veps_err = 0.0;
        *global_D_err = 0.0;
        //////////////////////
        // ** LOOP IN CELLS //
        //////////////////////
        for(int eN=0;eN<nElements_global;eN++)
          {
            //declare local storage for local contributions and initialize
            register double elementResidual_u[nDOF_test_element];
            double cell_I_err = 0., cell_Ieps_err = 0.,
              cell_V = 0., cell_V0 = 0., cell_sV = 0., cell_sV0 = 0.,
              cell_D_err = 0.;

            //loop over quadrature points and compute integrands
            for  (int k=0;k<nQuadraturePoints_element;k++)
              {
                //compute indeces and declare local storage
                register int eN_k = eN*nQuadraturePoints_element+k,
                  eN_k_nSpace = eN_k*nSpace,
                  eN_nDOF_trial_element = eN*nDOF_trial_element;
                register double
                  u, u0, uh,
                  u_grad_trial[nDOF_trial_element*nSpace],
                  grad_uh[nSpace],
                  //for general use
                  jac[nSpace*nSpace], jacDet, jacInv[nSpace*nSpace],
                  dV,x,y,z,h_phi;
                //get the physical integration weight
                ck.calculateMapping_element(eN,
                                            k,
                                            mesh_dof,
                                            mesh_l2g,
                                            mesh_trial_ref,
                                            mesh_grad_trial_ref,
                                            jac,
                                            jacDet,
                                            jacInv,
                                            x,y,z);
                ck.calculateH_element(eN,
                                      k,
                                      nodeDiametersArray,
                                      mesh_l2g,
                                      mesh_trial_ref,
                                      h_phi);
                dV = fabs(jacDet)*dV_ref[k];
                // get functions at quad points
                ck.valFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],uh);
                ck.valFromDOF(u0_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],u0);
                u = u_exact[eN_k];
                // get gradients
                ck.gradTrialFromRef(&u_grad_trial_ref[k*nDOF_trial_element*nSpace],jacInv,u_grad_trial);
                ck.gradFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],u_grad_trial,grad_uh);

                double epsHeaviside = epsFactHeaviside*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial;
                // compute (smoothed) heaviside functions //
                double Hu0 = heaviside(u0);
                double Hu = heaviside(u);
                double Huh = heaviside(uh);
                double sHu0 = smoothedHeaviside(epsHeaviside,u0);
                double sHu = smoothedHeaviside(epsHeaviside,u);
                double sHuh = smoothedHeaviside(epsHeaviside,uh);

                // compute cell metrics //
                cell_I_err += fabs(Hu - Huh)*dV;
                cell_Ieps_err += fabs(sHu - sHuh)*dV;

                cell_V   += Huh*dV;
                cell_V0  += Hu0*dV;
                cell_sV  += sHuh*dV;
                cell_sV0 += sHu0*dV;

                double norm2_grad_uh = 0.;
                for (int I=0; I<nSpace; I++)
                  norm2_grad_uh += grad_uh[I]*grad_uh[I];
                cell_D_err += std::pow(std::sqrt(norm2_grad_uh) - 1, 2.)*dV;
              }
            global_V += cell_V;
            global_V0 += cell_V0;
            global_sV += cell_sV;
            global_sV0 += cell_sV0;
            // metrics //
            *global_I_err    += cell_I_err;
            *global_Ieps_err += cell_Ieps_err;
            *global_D_err    += cell_D_err;
          }//elements
        *global_V_err = fabs(global_V0 - global_V)/global_V0;
        *global_Veps_err = fabs(global_sV0 - global_sV)/global_sV0;
        *global_D_err *= 0.5;
      }

      void calculateMetricsAtETS( // ETS=Every Time Step
                                 double dt,
                                 double* mesh_trial_ref,
                                 double* mesh_grad_trial_ref,
                                 double* mesh_dof,
                                 int* mesh_l2g,
                                 double* dV_ref,
                                 double* u_trial_ref,
                                 double* u_grad_trial_ref,
                                 double* u_test_ref,
                                 //physics
                                 int nElements_global,
                                 int useMetrics,
                                 int* u_l2g,
                                 double* elementDiameter,
                                 double* nodeDiametersArray,
                                 double degree_polynomial,
                                 double epsFactHeaviside,
                                 double* u_dof,
                                 double* u_dof_old,
                                 double* u0_dof,
                                 double* velocity,
                                 int offset_u, int stride_u,
                                 int numDOFs,
                                 double* global_R,
                                 double* global_Reps,
                                 double* global_V_err,
                                 double* global_Veps_err,
                                 double* global_D_err)
      {
        register double R_vector[numDOFs], Reps_vector[numDOFs];
        for (int i=0; i<numDOFs; i++)
          {
            R_vector[i] = 0.;
            Reps_vector[i] = 0.;
          }

        double global_V = 0.;
        double global_V0 = 0.;
        double global_sV = 0.;
        double global_sV0 = 0.;
        *global_R = 0.0;
        *global_Reps = 0.0;
        *global_V_err = 0.0;
        *global_Veps_err = 0.0;
        *global_D_err = 0.0;
        //////////////////////////////////////////////
        // ** LOOP IN CELLS FOR CELL BASED TERMS ** //
        //////////////////////////////////////////////
        for(int eN=0;eN<nElements_global;eN++)
          {
            //declare local storage for local contributions and initialize
            register double element_R[nDOF_test_element], element_Reps[nDOF_test_element];
            for (int i=0;i<nDOF_test_element;i++)
              {
                element_R[i] = 0.;
                element_Reps[i] = 0.;
              }
            double cell_R = 0., cell_Reps = 0.,
              cell_V = 0., cell_V0 = 0., cell_sV = 0., cell_sV0 = 0.,
              cell_D_err = 0.;
            //loop over quadrature points and compute integrands
            for  (int k=0;k<nQuadraturePoints_element;k++)
              {
                //compute indeces and declare local storage
                register int eN_k = eN*nQuadraturePoints_element+k,
                  eN_k_nSpace = eN_k*nSpace,
                  eN_nDOF_trial_element = eN*nDOF_trial_element;
                register double
                  unp1, un, u0,
                  grad_unp1[nSpace], sFlux_np1[nSpace], Flux_np1[nSpace],
                  u_grad_trial[nDOF_trial_element*nSpace],
                  u_grad_test_dV[nDOF_test_element*nSpace],
                  u_test_dV[nDOF_trial_element],
                  //for general use
                  jac[nSpace*nSpace], jacDet, jacInv[nSpace*nSpace],
                  dV,x,y,z,h_phi;
                //get the physical integration weight
                ck.calculateMapping_element(eN,
                                            k,
                                            mesh_dof,
                                            mesh_l2g,
                                            mesh_trial_ref,
                                            mesh_grad_trial_ref,
                                            jac,
                                            jacDet,
                                            jacInv,
                                            x,y,z);
                ck.calculateH_element(eN,
                                      k,
                                      nodeDiametersArray,
                                      mesh_l2g,
                                      mesh_trial_ref,
                                      h_phi);
                dV = fabs(jacDet)*dV_ref[k];
                // get functions at quad points
                ck.valFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],unp1);
                ck.valFromDOF(u_dof_old,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],un);
                ck.valFromDOF(u0_dof,&u_l2g[eN_nDOF_trial_element],&u_trial_ref[k*nDOF_trial_element],u0);
                // get gradients
                ck.gradTrialFromRef(&u_grad_trial_ref[k*nDOF_trial_element*nSpace],jacInv,u_grad_trial);
                ck.gradFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],u_grad_trial,grad_unp1);
                //precalculate test function products with integration weights for mass matrix terms
                for (int j=0;j<nDOF_trial_element;j++)
                  {
                    u_test_dV[j] = u_test_ref[k*nDOF_trial_element+j]*dV;
                    for (int I=0;I<nSpace;I++)
                      u_grad_test_dV[j*nSpace+I] = u_grad_trial[j*nSpace+I]*dV;
                  }

                double epsHeaviside = epsFactHeaviside*(useMetrics*h_phi+(1.0-useMetrics)*elementDiameter[eN])/degree_polynomial;
                // compute (smoothed) heaviside functions //
                double Hu0 = heaviside(u0);
                double Hunp1 = heaviside(unp1);
                double sHu0 = smoothedHeaviside(epsHeaviside,u0);
                double sHunp1 = smoothedHeaviside(epsHeaviside,unp1);

                // compute cell metrics //
                cell_V   += Hunp1*dV;
                cell_V0  += Hu0*dV;
                cell_sV  += sHunp1*dV;
                cell_sV0 += sHu0*dV;

                double norm2_grad_unp1 = 0.;
                for (int I=0; I<nSpace; I++)
                  norm2_grad_unp1 += grad_unp1[I]*grad_unp1[I];
                cell_D_err += std::pow(std::sqrt(norm2_grad_unp1) - 1, 2.)*dV;

                double Sunp1 = sign(unp1);
                double Sun = sign(un);
                double sSunp1 = smoothedSign(epsHeaviside,unp1);
                double sSun = smoothedSign(epsHeaviside,un);
                for (int I=0; I<nSpace; I++)
                  {
                    Flux_np1[I] = velocity[eN_k_nSpace+I]*Sunp1;
                    sFlux_np1[I] = velocity[eN_k_nSpace+I]*sSunp1;
                  }

                for(int i=0;i<nDOF_test_element;i++)
                  {
                    register int i_nSpace=i*nSpace;
                    element_R[i] += ((Sunp1-Sun)/dt*u_test_dV[i]
                                     + ck.Advection_weak(Flux_np1,&u_grad_test_dV[i_nSpace]));
                    element_Reps[i] += ((sSunp1-sSun)/dt*u_test_dV[i]
                                        + ck.Advection_weak(sFlux_np1,&u_grad_test_dV[i_nSpace]));
                  }
              }
            // DISTRIBUTE //
            for(int i=0;i<nDOF_test_element;i++)
              {
                int eN_i=eN*nDOF_test_element+i;
                int gi = offset_u+stride_u*u_l2g[eN_i]; //global i-th index
                R_vector[gi] += element_R[i];
                Reps_vector[gi] += element_Reps[i];
              }
            global_V += cell_V;
            global_V0 += cell_V0;
            global_sV += cell_sV;
            global_sV0 += cell_sV0;
            // metrics //
            *global_D_err    += cell_D_err;
          }//elements
        for (int i=0; i<numDOFs; i++)
          {
            *global_R += R_vector[i]*R_vector[i];
            *global_Reps += Reps_vector[i]*Reps_vector[i];
          }
        *global_V_err = fabs(global_V0 - global_V)/global_V0;
        *global_Veps_err = fabs(global_sV0 - global_sV)/global_sV0;
        *global_D_err *= 0.5;
      }

      void normalReconstruction(//element
                                double* mesh_trial_ref,
                                double* mesh_grad_trial_ref,
                                double* mesh_dof,
                                int* mesh_l2g,
                                double* dV_ref,
                                double* u_trial_ref,
                                double* u_grad_trial_ref,
                                double* u_test_ref,
                                //physics
                                int nElements_global,
                                int* u_l2g,
                                double* elementDiameter,
                                double* u_dof,
                                int offset_u, int stride_u,
                                // PARAMETERS FOR EDGE VISCOSITY
                                int numDOFs,
                                double* lumped_qx,
                                double* lumped_qy,
                                double* lumped_qz)
      {
        register double
          weighted_lumped_mass_matrix[numDOFs];
        for (int i=0; i<numDOFs; i++)
          {
            lumped_qx[i]=0.;
            lumped_qy[i]=0.;
            lumped_qz[i]=0.;
            weighted_lumped_mass_matrix[i]=0.;
          }
        for(int eN=0;eN<nElements_global;eN++)
          {
            //declare local storage for local contributions and initialize
            register double
              element_weighted_lumped_mass_matrix[nDOF_test_element],
              element_rhsx_normal_reconstruction[nDOF_test_element],
              element_rhsy_normal_reconstruction[nDOF_test_element],
              element_rhsz_normal_reconstruction[nDOF_test_element];
            for (int i=0;i<nDOF_test_element;i++)
              {
                element_weighted_lumped_mass_matrix[i]=0.0;
                element_rhsx_normal_reconstruction[i]=0.0;
                element_rhsy_normal_reconstruction[i]=0.0;
                element_rhsz_normal_reconstruction[i]=0.0;
              }
            //loop over quadrature points and compute integrands
            for(int k=0;k<nQuadraturePoints_element;k++)
              {
                //compute indeces and declare local storage
                register int eN_k = eN*nQuadraturePoints_element+k,
                  eN_k_nSpace = eN_k*nSpace,
                  eN_nDOF_trial_element = eN*nDOF_trial_element;
                register double
                  //for mass matrix contributions
                  grad_u[nSpace],
                  u_grad_trial[nDOF_trial_element*nSpace],
                  u_test_dV[nDOF_trial_element],
                  //for general use
                  jac[nSpace*nSpace], jacDet, jacInv[nSpace*nSpace],
                  dV,x,y,z;
                //get the physical integration weight
                ck.calculateMapping_element(eN,
                                            k,
                                            mesh_dof,
                                            mesh_l2g,
                                            mesh_trial_ref,
                                            mesh_grad_trial_ref,
                                            jac,
                                            jacDet,
                                            jacInv,
                                            x,y,z);
                dV = fabs(jacDet)*dV_ref[k];
                ck.gradTrialFromRef(&u_grad_trial_ref[k*nDOF_trial_element*nSpace],jacInv,u_grad_trial);
                ck.gradFromDOF(u_dof,&u_l2g[eN_nDOF_trial_element],u_grad_trial,grad_u);
                //precalculate test function products with integration weights for mass matrix terms
                for (int j=0;j<nDOF_trial_element;j++)
                  u_test_dV[j] = u_test_ref[k*nDOF_trial_element+j]*dV;

                double rhsx = grad_u[0];
                double rhsy = grad_u[1];
                double rhsz = 0;
                if (nSpace==3)
                  rhsz = grad_u[2];

                double norm_grad_u = 0;
                for (int I=0;I<nSpace; I++)
                  norm_grad_u += grad_u[I]*grad_u[I];
                norm_grad_u = std::sqrt(norm_grad_u);+1E-10;

                for(int i=0;i<nDOF_test_element;i++)
                  {
                    element_weighted_lumped_mass_matrix[i] += norm_grad_u*u_test_dV[i];
                    element_rhsx_normal_reconstruction[i] += rhsx*u_test_dV[i];
                    element_rhsy_normal_reconstruction[i] += rhsy*u_test_dV[i];
                    element_rhsz_normal_reconstruction[i] += rhsz*u_test_dV[i];
                  }
              } //k
            // DISTRIBUTE //
            for(int i=0;i<nDOF_test_element;i++)
              {
                int eN_i=eN*nDOF_test_element+i;
                int gi = offset_u+stride_u*u_l2g[eN_i]; //global i-th index

                weighted_lumped_mass_matrix[gi] += element_weighted_lumped_mass_matrix[i];
                lumped_qx[gi] += element_rhsx_normal_reconstruction[i];
                lumped_qy[gi] += element_rhsy_normal_reconstruction[i];
                lumped_qz[gi] += element_rhsz_normal_reconstruction[i];
              }//i
          }//elements
        // COMPUTE LUMPED L2 PROJECTION
        for (int i=0; i<numDOFs; i++)
          {
            double weighted_mi = weighted_lumped_mass_matrix[i];
            lumped_qx[i] /= weighted_mi;
            lumped_qy[i] /= weighted_mi;
            lumped_qz[i] /= weighted_mi;
          }
      }

    };//CLSVOF

  inline CLSVOF_base* newCLSVOF(int nSpaceIn,
                                int nQuadraturePoints_elementIn,
                                int nDOF_mesh_trial_elementIn,
                                int nDOF_trial_elementIn,
                                int nDOF_test_elementIn,
                                int nQuadraturePoints_elementBoundaryIn,
                                int CompKernelFlag)
  {
    if (nSpaceIn == 2)
      return proteus::chooseAndAllocateDiscretization2D<CLSVOF_base,CLSVOF,CompKernel>(nSpaceIn,
                                                                                       nQuadraturePoints_elementIn,
                                                                                       nDOF_mesh_trial_elementIn,
                                                                                       nDOF_trial_elementIn,
                                                                                       nDOF_test_elementIn,
                                                                                       nQuadraturePoints_elementBoundaryIn,
                                                                                       CompKernelFlag);
    else
      return proteus::chooseAndAllocateDiscretization<CLSVOF_base,CLSVOF,CompKernel>(nSpaceIn,
                                                                                     nQuadraturePoints_elementIn,
                                                                                     nDOF_mesh_trial_elementIn,
                                                                                     nDOF_trial_elementIn,
                                                                                     nDOF_test_elementIn,
                                                                                     nQuadraturePoints_elementBoundaryIn,
                                                                                     CompKernelFlag);
  }
}//proteus
#endif