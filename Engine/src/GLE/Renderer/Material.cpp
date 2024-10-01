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
        if(sMaterials.contains(id)) {
            return sMaterials[id];
        }

        GLE_ASSERT(false, "Invalid Material ID!");
        return nullptr;
    }
}
