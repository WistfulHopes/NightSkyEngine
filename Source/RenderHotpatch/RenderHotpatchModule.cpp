class FRenderHotpatchModule : public IModuleInterface
{
    virtual void StartupModule() override
    {
        // Hook to map changes to toggle back to the mobile preview.
        FEditorDelegates::MapChange.AddRaw(this, &FRenderHotpatchModule::OnMapChange);
    }

    virtual void ShutdownModule() override
    {
        FEditorDelegates::MapChange.RemoveAll(this);
    }

    void OnMapChange(uint32)
    {
        check(GEditor);

        // Force the editor into DirectX Mobile Preview on ES31
        // Stole these settings from Engine/Config/Windows/DataDrivenPlatformInfo.ini
        const FPreviewPlatformInfo PreviewPlatform(
            ERHIFeatureLevel::ES3_1,
            EShaderPlatform::SP_PCD3D_ES3_1,
            FName("PC"),
            FName("PCD3D_ES31"),
            FName("Windows_Preview_ES31"),
            true,
            FName("PCD3D_ES3_1_Preview")
            );
        
        GEditor->SetPreviewPlatform(PreviewPlatform, false);
    }
};

IMPLEMENT_MODULE(FRenderHotpatchModule, RenderHotpatch);
