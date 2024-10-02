//
// Created by Andrew Graser on 9/13/2024.
//

#include "Material.h"

namespace GLE {
    std::unordered_map<MaterialID, std::shared_ptr<Material>> sMaterials;

    MaterialID Material::DefaultMaterial;

    MaterialID Material::Create()
    {
        auto mat = std::make_shared<Material>();
        sMaterials.emplace(mat->GetID(), mat);
        return mat->GetID();
    }

    std::shared_ptr<Material> Material::Get(MaterialID id)
    {
        if(id == 0) return nullptr;

        if(sMaterials.contains(id)) {
            return sMaterials[id];
        }

        GLE_ASSERT(false, "Invalid Material ID!");
        return nullptr;
    }

    std::vector<std::shared_ptr<Material>> Material::GetMaterials()
    {
        std::vector<std::shared_ptr<Material>> mats;

        for(auto& [id, material] : sMaterials) {
            mats.push_back(material);
        }

        return mats;
    }

    std::vector<MaterialID> Material::GetIDS()
    {
        std::vector<MaterialID> mats;

        for(auto& [id, material] : sMaterials) {
            mats.push_back(id);
        }

        return mats;
    }
}
