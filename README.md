# BFV-OcclusionQueryManager
I reversed how the game sets the m_occluded for the ClientSoldierEntity using the SoldierOcclusionQueryManager and build my own OcclusionQueryManager from that using the games WorldOcclusionQueryRenderModule.<br />
My CustomOcclusionQueryManager can then be used to check a vehicle for occlusion.<br />
Look at my other project for a working implementation<br />
https://github.com/Speedi13/BFV-SimpleCheat <br />
https://i.imgur.com/HOBbVYt.mp4 <br />
# Reversed functions
All IDA-Pseudo code I generated to reverse the is here:<br />
https://github.com/Speedi13/BFV-OcclusionQueryManager/blob/master/Reversed_Occlusion_functions.h <br />

All IDA structs to import if you want to take a look too<br />
https://github.com/Speedi13/BFV-OcclusionQueryManager/blob/master/Reversed_Occlusion_IDA_structs.h <br />

# CustomOcclusionQueryManager usage
Import the classes <br />
https://github.com/Speedi13/BFV-OcclusionQueryManager/blob/master/Reversed_Occlusion_classes.h <br />
```cpp
//once every frame
CustomOcclusionQueryManager::GetInstance()->UpdateLocalTransform( &vLocalPos );
```

```cpp
//in your entity loop
fb::LinearTransform_AABB TransformAABB = {};
pVehicle->GetTransformAABB( TransformAABB );

CustomOcclusionQueryManager::OcclusionQuery* pQuery = CustomOcclusionQueryManager::GetInstance()->GetQuery( pVehicle );
if (pQuery == NULL)
    pQuery = CustomOcclusionQueryManager::GetInstance()->AddQuery( pVehicle, NULL );
pQuery->UpdateQuery( &TransformAABB );

bVehicleVisible = pQuery->IsVisible();
```

