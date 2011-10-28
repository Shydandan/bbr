/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 */

#include "ccnx-producer-helper.h"

NS_LOG_COMPONENT_DEFINE ("CcnxProducerHelper");

namespace ns3 
{
    
CcnxProducerHelper::CcnxProducerHelper (const std::string &prefix, uint32_t virtualPayloadSize)
{
    m_factory.SetTypeId ("ns3::CcnxProducer");
    
    CcnxNameComponentsValue prefixValue;
    prefixValue.DeserializeFromString (prefix, MakeCcnxNameComponentsChecker ());
    m_factory.Set ("Prefix", prefixValue);
    
    m_factory.Set ("PayloadSize", UintegerValue (virtualPayloadSize));
}
    
void 
CcnxProducerHelper::SetAttribute (std::string name, const AttributeValue &value)
{
    m_factory.Set (name, value);
}
    
ApplicationContainer
CcnxProducerHelper::Install (Ptr<Node> node)
{
    NS_LOG_FUNCTION(this);
    return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
CcnxProducerHelper::Install (std::string nodeName)
{
    Ptr<Node> node = Names::Find<Node> (nodeName);
    return ApplicationContainer (InstallPriv (node));
}
    
ApplicationContainer
CcnxProducerHelper::Install (NodeContainer c)
{
    ApplicationContainer apps;
    for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
        apps.Add (InstallPriv (*i));
    }
        
    return apps;
}
    
    /*CcnxStackHelper::CreateAndAggregateObjectFromTypeId (Ptr<Node> node, const std::string typeId)
    {
        ObjectFactory factory;
        factory.SetTypeId (typeId);
        Ptr<Object> protocol = factory.Create <Object> ();
        node->AggregateObject (protocol);
    }*/
Ptr<Application>
CcnxProducerHelper::InstallPriv (Ptr<Node> node)
{
    NS_LOG_INFO ("InstallPriv started");
    Ptr<CcnxProducer> app = m_factory.Create<CcnxProducer> ();        
    node->AddApplication (app);

    /*Ptr<CcnxLocalFace> localFace = Create<CcnxLocalFace> ();
    localFace->SetNode(node);
        
    //CreateAndAggregateObjectFromTypeId (node, "ns3::CcnxL3Protocol");
    ObjectFactory factory;
    factory.SetTypeId("ns3::CcnxL3Protocol");
    Ptr<Object> protocol = factory.Create<Object> ();
    node->AggregateObject(protocol);
    
    Ptr<Ccnx> ccnx = node->GetObject<Ccnx> ();
    
    if (ccnx == NULL)
    {
        NS_FATAL_ERROR ("CcnxProducerHelper::InstallPriv (): Getting Ccnx " 
                        "a CcnxStack must be installed on the node");
        return 0;
    }

    // m_factory.Set ("Face", PointerValue (localFace));
    m_factory.Set ("Ccnx", PointerValue (ccnx));
    Ptr<CcnxProducer> app = m_factory.Create<CcnxProducer> ();

    //app->m_ccnx->m_contentStore->SetMaxSize(app->GetStoreCapacity());
    localFace->RegisterProtocolHandler (MakeCallback (&CcnxProducer::HandlePacket, app));
    localFace->SetUp();
        
    node->AddApplication (app);*/
        
    return app;
}
}
