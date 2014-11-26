/**
 * GPGPU adaptive thresholding processor: Implementation of individual passes.
 */
#ifndef OGLES_GPGPU_COMMON_PROC_ADAPT_THRESH_PASS
#define OGLES_GPGPU_COMMON_PROC_ADAPT_THRESH_PASS

#include "../../common_includes.h"

#include "../base/filterprocbase.h"

namespace ogles_gpgpu {
class AdaptThreshProcPass : public FilterProcBase {
public:
    /**
     * Construct as render pass <pass> (1 or 2).
     */
    AdaptThreshProcPass(int pass) : FilterProcBase(),
                                    renderPass(pass),
                                    pxDx(0.0f),
                                    pxDy(0.0f)
    {
        assert(renderPass == 1 || renderPass == 2);
    }
    
    /**
     * Init the processor for input frames of size <inW>x<inH> which is at
     * position <order> in the processing pipeline.
     */
    virtual int init(int inW, int inH, unsigned int order, bool prepareForExternalInput = false);
    
    /**
     * Create a texture that is attached to the FBO and will contain the processing result.
     * Set <genMipmap> to true to generate a mipmap (usually only works with POT textures).
     * Overrides ProcBase's method.
     */
    virtual void createFBOTex(bool genMipmap);
    
    /**
     * Render the output.
     */
    virtual void render();
    
private:
    int renderPass; // render pass number. must be 1 or 2
    
	GLint shParamUPxD;		// pixel delta values for texture lookup in the fragment shader. only used for adapt. thresholding
    
	float pxDx;	// pixel delta value for texture access. only used for adapt. thresholding
	float pxDy;	// pixel delta value for texture access. only used for adapt. thresholding
    
    static const char *fshaderAdaptThreshPass1Src;  // fragment shader source for adaptive thresholding pass 1
    static const char *fshaderAdaptThreshPass2Src;  // fragment shader source for adaptive thresholding pass 2
};
}

#endif