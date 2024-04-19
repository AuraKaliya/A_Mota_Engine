package.path="./?.lua;"..package.path;

local engine=require "engine";
local object=require "gameobject";
local item=require "item";

function init(itemId,objectId)
    print("init");
    item.init(itemId);
    object.init(objectId);

end

rState=false;

function tick()

    if(readKeyState("w") or readKeyState("s") or readKeyState("a") or readKeyState("d") or readKeyState("r")) then

        if(readKeyState("w")) then 
            setObjectState(object.Id,"nowState","Up");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",2,1);
            --setObjectState(object.Id,"posY",getObjectState(object.Id,"posY")-5);
        end
        if(readKeyState("s")) then 
            setObjectState(object.Id,"nowState","Down");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",4,1);
            --setObjectState(object.Id,"posY",getObjectState(object.Id,"posY")+5);
     
        end
        if(readKeyState("a")) then 
            setObjectState(object.Id,"nowState","Left");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",3,1);
            --setObjectState(object.Id,"posX",getObjectState(object.Id,"posX")-5);

        end
        if(readKeyState("d")) then 
            setObjectState(object.Id,"nowState","Right");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",1,1);
            --setObjectState(object.Id,"posX",getObjectState(object.Id,"posX")+5);
        end
        
        if(readKeyState("r")) then
            if(rState==false)  then
            rState=true;
            soluteInstruction(object.Id,"heroMoveToNextLayer","Demo",0);
            end
        end 
    else

    setObjectState(object.Id,"nowState","Normal"); 
    rState=false;

    end

end
