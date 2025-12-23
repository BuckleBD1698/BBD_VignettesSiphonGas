class ActionSiphonWreckCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(5.0);
    }
}

class ActionSiphonWreck : ActionContinuousBase
{
    // TODO: can I do this better than strings? enfusion hates set vector for some reason
    static ref set<string> m_SiphonedWrecks;

    void ActionSiphonWreck()
    {
        m_CallbackClass = ActionSiphonWreckCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_EMPTY_VESSEL;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
        m_Text = "Siphon Fuel";
        
        if (!m_SiphonedWrecks)
        {
            m_SiphonedWrecks = new set<string>;
        }
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTCursor;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (!targetObject) return false;

        string type = targetObject.GetType();
        type.ToLower();
        
        if (!type.Contains("wreck") && !type.Contains("volha_01_abandoned") && !type.Contains("land_v3s_01")) return false;

        if (m_SiphonedWrecks.Find(targetObject.GetPosition().ToString()) != -1) return false;

        if (item.GetQuantity() >= item.GetQuantityMax()) return false;
        
        int liquidType = item.GetLiquidType();
        if (liquidType != LIQUID_GASOLINE && liquidType != LIQUID_NONE) return false;

        return true;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        Object targetObject = action_data.m_Target.GetObject();
        ItemBase container = action_data.m_MainItem;
        
        if (targetObject && container)
        {
            m_SiphonedWrecks.Insert(targetObject.GetPosition().ToString());

            float maxQty = container.GetQuantityMax();
            float addQty = Math.RandomFloat(maxQty * 0.1, maxQty * 0.4);
            
            container.SetLiquidType(LIQUID_GASOLINE);
            container.AddQuantity(addQty);
        }
    }
}