/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrTextureProxy_DEFINED
#define GrTextureProxy_DEFINED

#include "../gpu/GrSamplerState.h"
#include "GrSurfaceProxy.h"

class GrCaps;
class GrDeferredProxyUploader;
class GrResourceCache;
class GrResourceProvider;
class GrTextureOpList;
class GrTextureProxyPriv;

// This class delays the acquisition of textures until they are actually required
class GrTextureProxy : virtual public GrSurfaceProxy {
public:
    GrTextureProxy* asTextureProxy() override { return this; }
    const GrTextureProxy* asTextureProxy() const override { return this; }

    // Actually instantiate the backing texture, if necessary
    bool instantiate(GrResourceProvider*) override;

    GrSamplerState::Filter highestFilterMode() const;

    GrSLType imageStorageType() const {
        if (GrPixelConfigIsSint(this->config())) {
            return kIImageStorage2D_GrSLType;
        } else {
            return kImageStorage2D_GrSLType;
        }
    }

    bool isMipMapped() const { return fIsMipMapped; }

    /**
     * Return the texture proxy's unique key. It will be invalid if the proxy doesn't have one.
     */
    const GrUniqueKey& getUniqueKey() const {
#ifdef SK_DEBUG
        if (fTarget && fUniqueKey.isValid()) {
            SkASSERT(fTarget->getUniqueKey().isValid());
            // It is possible for a non-keyed proxy to have a uniquely keyed resource assigned to
            // it. This just means that a future user of the resource will be filling it with unique
            // data. However, if the proxy has a unique key its attached resource should also
            // have that key.
            SkASSERT(fUniqueKey == fTarget->getUniqueKey());
        }
#endif

        return fUniqueKey;
    }

    /**
     * Internal-only helper class used for manipulations of the resource by the cache.
     */
    class CacheAccess;
    inline CacheAccess cacheAccess();
    inline const CacheAccess cacheAccess() const;

    // Provides access to special purpose functions.
    GrTextureProxyPriv texPriv();
    const GrTextureProxyPriv texPriv() const;

protected:
    friend class GrSurfaceProxy; // for ctors
    friend class GrTextureProxyPriv;

    // Deferred version
    GrTextureProxy(const GrSurfaceDesc& srcDesc, SkBackingFit, SkBudgeted,
                   const void* srcData, size_t srcRowBytes, uint32_t flags);
    // Wrapped version
    GrTextureProxy(sk_sp<GrSurface>, GrSurfaceOrigin);

    ~GrTextureProxy() override;

    SkDestinationSurfaceColorMode mipColorMode() const { return fMipColorMode;  }

    sk_sp<GrSurface> createSurface(GrResourceProvider*) const override;

private:
    bool fIsMipMapped;
    SkDestinationSurfaceColorMode fMipColorMode;

    GrUniqueKey fUniqueKey;
    GrResourceCache* fCache; // only set when fUniqueKey is valid

    // Only used for proxies whose contents are being prepared on a worker thread. This object
    // stores the texture data, allowing the proxy to remain uninstantiated until flush. At that
    // point, the proxy is instantiated, and this data is used to perform an ASAP upload.
    std::unique_ptr<GrDeferredProxyUploader> fDeferredUploader;

    size_t onUninstantiatedGpuMemorySize() const override;

    // Methods made available via GrTextureProxy::CacheAccess
    void setUniqueKey(GrResourceCache*, const GrUniqueKey&);
    void clearUniqueKey();

    // For wrapped proxies the GrTexture pointer is stored in GrIORefProxy.
    // For deferred proxies that pointer will be filled in when we need to instantiate
    // the deferred resource

    typedef GrSurfaceProxy INHERITED;
};

#endif
