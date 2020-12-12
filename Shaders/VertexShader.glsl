
attribute vec4 a_Position;	        // in: Posición de cada vértice
attribute vec3 a_Normal;	        // in: Normal de cada vértice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (cámara)
uniform vec4 u_Color;		        // in: Color del objeto



uniform int  u_Luz0;                // in: Indica si la luz 0 está encedida
uniform float  u_Luz_Intensity_0;
uniform float  u_Luz_X_0;
uniform float  u_Luz_Y_0;
uniform float  u_Luz_Z_0;


uniform int  u_Luz1;                // in: Indica si la luz 1 está encedida
uniform float  u_Luz_Intensity_1;
uniform float  u_Luz_X_1;
uniform float  u_Luz_Y_1;
uniform float  u_Luz_Z_1;

uniform int  u_Luz2;                // in: Indica si la luz 2 está encedida
uniform float  u_Luz_Intensity_2;
uniform float  u_Luz_X_2;
uniform float  u_Luz_Y_2;
uniform float  u_Luz_Z_2;

varying vec4 v_Color;		        // out: Color al fragment shader

void main()
{
    // Luz0
    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posición del vértice
	vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del vértice
    float resultado = 0.0;
	float ambient = 0.15;                               // (15% de int. ambiente)
	float diffuse = 0.0;



	vec4 LightPos0 = u_VMatrix*vec4( u_Luz_X_0, u_Luz_Y_0, u_Luz_Z_0, 1);		// Posición de la luz [fija]
	float d0 = length(LightPos0.xyz - P);			        // distancia de la luz
	vec3  L0 = normalize(LightPos0.xyz - P);			    // Vector Luz
	if (u_Luz0>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L0), 0.0);		            // Cálculo de la int. difusa
        // Cálculo de la atenuación
        float attenuation = 80.0/(0.25+(0.01*d0)+(0.003*d0*d0));
        resultado += diffuse*attenuation * u_Luz_Intensity_0;
	}



    // Luz1
    vec4 LightPos1 = u_VMatrix*vec4( u_Luz_X_1, u_Luz_Y_1, u_Luz_Z_1, 1);
	float d1 = length(LightPos1.xyz - P);
	vec3  L1 = normalize(LightPos1.xyz - P);
	if (u_Luz1>0) {
        diffuse = max(dot(N, L1), 0.0);
        float attenuation = 80.0/(0.25+(0.01*d1)+(0.003*d1*d1));
        resultado += diffuse*attenuation * u_Luz_Intensity_1;
	}

    // Luz2
    vec4 LightPos2 = u_VMatrix*vec4( u_Luz_X_2, u_Luz_Y_2, u_Luz_Z_2, 1);
	float d2 = length(LightPos2.xyz - P);
	vec3  L2 = normalize(LightPos2.xyz - P);
	if (u_Luz2>0) {
        diffuse = max(dot(N, L2), 0.0);
        float attenuation = 80.0/(0.25+(0.01*d2)+(0.003*d2*d2));
        resultado += diffuse*attenuation * u_Luz_Intensity_2;
	}



	v_Color = u_Color * resultado;
	gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
