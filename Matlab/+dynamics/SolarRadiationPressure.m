function a = SolarRadiationPressure(r,r_Primary,r_Secondary,r_Sun,r_SunSSB,Area,mass,Cr,P0,AU,shm,ConstantParameters)
%{
© 2025 Yazan Chihabi
%}
%--------------------------------------------------------------------------
%    Montenbruck, O. and Gill, E., Satellite Orbits: Models, Methods, and
%    Applications, Springer, 2001. 
% Calculates the perturbing acceleration of solar radiation pressure
%
% Inputs:
%   r               Spacecraft position vector 
%   r_Primary	    Primary body position vector (Barycentric)
%   r_Secondary		Secondary position vector (geocentric)
%   r_Sun       Sun position vector (geocentric)
%   r_SunSSB    Sun position vector (Barycentric)
%   Area        Cross-section 
%   mass        Spacecraft mass
%   Cr          Solar radiation pressure coefficient
%   P0          Solar radiation pressure at 1 AU 
%   AU          Length of one Astronomical Unit
%   shm         Shadow model (geometrical or cylindrical)
%
% Output:
%   a    		Acceleration (km/s^2)
%
% 
%--------------------------------------------------------------------------

%                                          Vector     Distance
% Second body wrt primary body             pccor      rpc
%        primary body wrt Sun              ccor       rc
%        secondary body wrt Sun            pscor      rps   
%        Satellite wrt primary body        sbcor      rsb  
%        Satellite wrt Sun                 bcor       rb 
%        Satellite wrt secondary body      sbpcor     rsbp
pccor = r_Secondary;
ccor = r_Primary-r_SunSSB;
pscor = r_Secondary-r_Sun;
sbcor = r;
bcor = r-r_Sun;
sbpcor = r-r_Secondary;

if ( strcmp(shm,'cylindrical') )
    nu = dynamics.Cylindrical(r,r_Sun);
else
    [nu,~] = dynamics.Shadow(pccor,ccor,pscor,sbcor,bcor,sbpcor,ConstantParameters);
end

% Acceleration
a = -nu*P0/(norm(r_Sun)^2)*AU*AU/mass*(Area*(2-Cr)*bcor/(norm(bcor)) + (2*(Cr-1)*Area*(-bcor/(norm(bcor)))));

end
