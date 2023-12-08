package.path="./?.lua;"..package.path;

local engine=require "engine";
local object=require "gameobject";
local item=require "item";


testname="hahahahahahahahahahahahahahahahahah";

function init(itemId,objectId)
    print("init");
    item.init(itemId);
    object.init(objectId);

end

timerState=0;
timerIndex=0;
timerIndexMax=30;

tickFlag=false;

function tick()
    print("test1---tick --up and down");
    print(object.Id);
    timerIndex=timerIndex+1;
    if(timerIndex>timerIndexMax) then
        timerIndex=0;
        timerState=timerState+1;
         if(timerState>3) then
             timerState=0;
         end
    end

    if(timerState==0) then
        print("hahaha");
        setObjectState(object.Id,"nowState","Up");
        soluteInstruction(object.Id,"monsterMoveToNextElement","Demo",2,1);
    elseif(timerState==1) then
        setObjectState(object.Id,"nowState","Normal"); 
    elseif(timerState==2) then
        setObjectState(object.Id,"nowState","Down");
        soluteInstruction(object.Id,"monsterMoveToNextElement","Demo",4,1);
    elseif(timerState==3)  then
        setObjectState(object.Id,"nowState","Normal"); 
    end

end
