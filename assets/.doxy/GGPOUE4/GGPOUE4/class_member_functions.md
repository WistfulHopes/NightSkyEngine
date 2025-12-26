
# Class Member Functions



## a

* **AddConnection** ([**ConnectionManager**](class_connection_manager.md))
* **AddLocalInput** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**Sync**](class_sync.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **AddPlayer** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **AddDelayedInputToQueue** ([**InputQueue**](class_input_queue.md))
* **AddInput** ([**InputQueue**](class_input_queue.md))
* **AdvanceQueueHead** ([**InputQueue**](class_input_queue.md))
* **AddRemotePlayer** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **AddSpectator** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **AddRemoteInput** ([**Sync**](class_sync.md))
* **AdjustSimulation** ([**Sync**](class_sync.md))
* **advance\_frame** ([**TimeSync**](class_time_sync.md))
* **AllUniqueAddresses** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **AllValidAddresses** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))


## b

* **bool** ([**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md))
* **BeginLog** ([**SyncTestBackend**](class_sync_test_backend.md))


## c

* **ConnectionInfo** ([**ConnectionInfo**](class_connection_info.md))
* **ConnectionManager** ([**ConnectionManager**](class_connection_manager.md))
* **Chat** ([**GGPOSession**](struct_g_g_p_o_session.md))
* **clear** ([**GameInput**](struct_game_input.md))
* **CheckInitialSync** ([**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md))
* **ComputeWaitTime** ([**Poll**](class_poll.md))
* **CheckSimulation** ([**Sync**](class_sync.md))
* **CheckSimulationConsistency** ([**Sync**](class_sync.md))
* **CreateQueues** ([**Sync**](class_sync.md))
* **CreateNetwork** ([**UGGPOGameInstance**](class_u_g_g_p_o_game_instance.md), [**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **CreateLocalAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **CreateNetworkAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **ClearSendQueue** ([**UdpProtocol**](class_udp_protocol.md))
* **CreateSocket** ([**UdpProtocol**](class_udp_protocol.md))


## d

* **DisconnectPlayer** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md))
* **DoPoll** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **desc** ([**GameInput**](struct_game_input.md))
* **DiscardConfirmedFrames** ([**InputQueue**](class_input_queue.md))
* **DisconnectPlayerQueue** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **Disconnect** ([**UdpProtocol**](class_udp_protocol.md))
* **DispatchMsg** ([**UdpProtocol**](class_udp_protocol.md))
* **Destroy** ([**neosmart::neosmart\_wfmo\_t\_**](structneosmart_1_1neosmart__wfmo__t__.md))


## e

* **equal** ([**GameInput**](struct_game_input.md))
* **erase** ([**GameInput**](struct_game_input.md))
* **empty** ([**RingBuffer**](class_ring_buffer.md))
* **EndLog** ([**SyncTestBackend**](class_sync_test_backend.md))
* **Event** ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md))


## f

* **front** ([**RingBuffer**](class_ring_buffer.md))
* **FindSavedFrameIndex** ([**Sync**](class_sync.md))


## g

* **ggpo\_add\_local\_input** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_add\_player** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_advance\_frame** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_close\_session** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_disconnect\_player** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_get\_network\_stats** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_idle** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_set\_disconnect\_notify\_start** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_set\_disconnect\_timeout** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_set\_frame\_delay** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_start\_session** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_start\_spectating** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_start\_synctest** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_synchronize\_input** ([**GGPONet**](class_g_g_p_o_net.md))
* **ggpo\_try\_synchronize\_local** ([**GGPONet**](class_g_g_p_o_net.md))
* **GetNetworkStats** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**UdpProtocol**](class_udp_protocol.md))
* **GetConfirmedInput** ([**InputQueue**](class_input_queue.md))
* **GetFirstIncorrectFrame** ([**InputQueue**](class_input_queue.md))
* **GetInput** ([**InputQueue**](class_input_queue.md))
* **GetLastConfirmedFrame** ([**InputQueue**](class_input_queue.md))
* **GetLength** ([**InputQueue**](class_input_queue.md))
* **GetConfirmedInputs** ([**Sync**](class_sync.md))
* **GetEvent** ([**Sync**](class_sync.md), [**UdpProtocol**](class_udp_protocol.md))
* **GetFrameCount** ([**Sync**](class_sync.md))
* **GetLastSavedFrame** ([**Sync**](class_sync.md))
* **GetAddress** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **GetLocalPort** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **GetPlayerIndex** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **GetIpAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **GetIpAddressString** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **GetPort** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **GGPONetworkStats** ([**UdpProtocol**](class_udp_protocol.md))
* **GetPeerConnectStatus** ([**UdpProtocol**](class_udp_protocol.md))


## h

* **HandlesMsg** ([**UdpProtocol**](class_udp_protocol.md))


## i

* **IncrementFrame** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**Sync**](class_sync.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **init** ([**GameInput**](struct_game_input.md))
* **is\_null** ([**GameInput**](struct_game_input.md))
* **Init** ([**InputQueue**](class_input_queue.md), [**Sync**](class_sync.md), [**Udp**](class_udp.md), [**UdpProtocol**](class_udp_protocol.md))
* **InputQueue** ([**InputQueue**](class_input_queue.md))
* **item** ([**RingBuffer**](class_ring_buffer.md))
* **InRollback** ([**Sync**](class_sync.md))
* **IsSameAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **IsValidAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **IsInitialized** ([**UdpProtocol**](class_udp_protocol.md))
* **IsRunning** ([**UdpProtocol**](class_udp_protocol.md))
* **IsSynchronized** ([**UdpProtocol**](class_udp_protocol.md))


## l

* **Log** ([**ConnectionManager**](class_connection_manager.md), [**InputQueue**](class_input_queue.md), [**Udp**](class_udp.md), [**UdpProtocol**](class_udp_protocol.md))
* **Logv** ([**GGPOSession**](struct_g_g_p_o_session.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **log** ([**GameInput**](struct_game_input.md))
* **LoadFrame** ([**Sync**](class_sync.md))
* **LogSaveStates** ([**SyncTestBackend**](class_sync_test_backend.md))
* **LogEvent** ([**UdpProtocol**](class_udp_protocol.md))
* **LogMsg** ([**UdpProtocol**](class_udp_protocol.md))


## n

* **NumPlayers** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))


## o

* **OnHandlePoll** ([**IPollSink**](class_i_poll_sink.md))
* **OnLoopPoll** ([**IPollSink**](class_i_poll_sink.md), [**Udp**](class_udp.md), [**UdpProtocol**](class_udp_protocol.md))
* **OnMsgPoll** ([**IPollSink**](class_i_poll_sink.md))
* **OnPeriodicPoll** ([**IPollSink**](class_i_poll_sink.md))
* **OnMsg** ([**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**Udp::Callbacks**](struct_udp_1_1_callbacks.md), [**UdpProtocol**](class_udp_protocol.md))
* **OnSyncEvent** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **OnUdpProtocolEvent** ([**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md))
* **OnUdpProtocolPeerEvent** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **OnUdpProtocolSpectatorEvent** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **operator[]** ([**StaticBuffer**](class_static_buffer.md))
* **OnInput** ([**UdpProtocol**](class_udp_protocol.md))
* **OnInputAck** ([**UdpProtocol**](class_udp_protocol.md))
* **OnInvalid** ([**UdpProtocol**](class_udp_protocol.md))
* **OnKeepAlive** ([**UdpProtocol**](class_udp_protocol.md))
* **OnQualityReply** ([**UdpProtocol**](class_udp_protocol.md))
* **OnQualityReport** ([**UdpProtocol**](class_udp_protocol.md))
* **OnSyncReply** ([**UdpProtocol**](class_udp_protocol.md))
* **OnSyncRequest** ([**UdpProtocol**](class_udp_protocol.md))


## p

* **Peer2PeerBackend** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **PlayerHandleToQueue** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **Poll2Players** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **PollNPlayers** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **PollSyncEvents** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **PollUdpProtocolEvents** ([**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md))
* **Poll** ([**Poll**](class_poll.md))
* **PollPeriodicSinkCb** ([**Poll::PollPeriodicSinkCb**](struct_poll_1_1_poll_periodic_sink_cb.md))
* **PollSinkCb** ([**Poll::PollSinkCb**](struct_poll_1_1_poll_sink_cb.md))
* **Pump** ([**Poll**](class_poll.md))
* **pop** ([**RingBuffer**](class_ring_buffer.md))
* **push** ([**RingBuffer**](class_ring_buffer.md))
* **push\_back** ([**StaticBuffer**](class_static_buffer.md))
* **PacketSize** ([**UdpMsg**](struct_udp_msg.md))
* **PayloadSize** ([**UdpMsg**](struct_udp_msg.md))
* **PumpSendQueue** ([**UdpProtocol**](class_udp_protocol.md))


## q

* **QueueToPlayerHandle** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **QueueToSpectatorHandle** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **QueueEvent** ([**UdpProtocol**](class_udp_protocol.md))
* **QueueEntry** ([**UdpProtocol::QueueEntry**](struct_udp_protocol_1_1_queue_entry.md))


## r

* **RecvFrom** ([**ConnectionManager**](class_connection_manager.md))
* **ResetManager** ([**ConnectionManager**](class_connection_manager.md))
* **ResetPrediction** ([**InputQueue**](class_input_queue.md), [**Sync**](class_sync.md))
* **RegisterHandle** ([**Poll**](class_poll.md))
* **RegisterLoop** ([**Poll**](class_poll.md))
* **RegisterMsgLoop** ([**Poll**](class_poll.md))
* **RegisterPeriodic** ([**Poll**](class_poll.md))
* **Run** ([**Poll**](class_poll.md))
* **RingBuffer** ([**RingBuffer**](class_ring_buffer.md))
* **RaiseSyncError** ([**SyncTestBackend**](class_sync_test_backend.md))
* **recommend\_frame\_wait\_duration** ([**TimeSync**](class_time_sync.md))
* **RecommendFrameDelay** ([**UdpProtocol**](class_udp_protocol.md))


## s

* **SendTo** ([**ConnectionManager**](class_connection_manager.md), [**Udp**](class_udp.md))
* **ShutdownModule** ([**FGGPOUE4Module**](class_f_g_g_p_o_u_e4_module.md))
* **StartupModule** ([**FGGPOUE4Module**](class_f_g_g_p_o_u_e4_module.md))
* **SetDisconnectNotifyStart** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**UdpProtocol**](class_udp_protocol.md))
* **SetDisconnectTimeout** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**UdpProtocol**](class_udp_protocol.md))
* **SetFrameDelay** ([**GGPOSession**](struct_g_g_p_o_session.md), [**InputQueue**](class_input_queue.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**Sync**](class_sync.md))
* **SyncInput** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md), [**SpectatorBackend**](class_spectator_backend.md), [**SyncTestBackend**](class_sync_test_backend.md))
* **set** ([**GameInput**](struct_game_input.md))
* **size** ([**RingBuffer**](class_ring_buffer.md), [**StaticBuffer**](class_static_buffer.md))
* **SpectatorBackend** ([**SpectatorBackend**](class_spectator_backend.md))
* **StaticBuffer** ([**StaticBuffer**](class_static_buffer.md))
* **SaveCurrentFrame** ([**Sync**](class_sync.md))
* **SetLastConfirmedFrame** ([**Sync**](class_sync.md))
* **Sync** ([**Sync**](class_sync.md))
* **SavedFrame** ([**Sync::SavedFrame**](struct_sync_1_1_saved_frame.md))
* **SynchronizeInputs** ([**Sync**](class_sync.md))
* **SyncTestBackend** ([**SyncTestBackend**](class_sync_test_backend.md))
* **SendInput** ([**UdpProtocol**](class_udp_protocol.md))
* **SendInputAck** ([**UdpProtocol**](class_udp_protocol.md))
* **SendMsg** ([**UdpProtocol**](class_udp_protocol.md))
* **SendPendingOutput** ([**UdpProtocol**](class_udp_protocol.md))
* **SendSyncRequest** ([**UdpProtocol**](class_udp_protocol.md))
* **SetLocalFrameNumber** ([**UdpProtocol**](class_udp_protocol.md))
* **Synchronize** ([**UdpProtocol**](class_udp_protocol.md))


## t

* **ToString** ([**ConnectionInfo**](class_connection_info.md), [**ConnectionManager**](class_connection_manager.md))
* **TrySynchronizeLocal** ([**GGPOSession**](struct_g_g_p_o_session.md), [**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **TimeSync** ([**TimeSync**](class_time_sync.md))


## u

* **UGGPONetwork** ([**UGGPONetwork**](class_u_g_g_p_o_network.md))
* **UGGPONetworkAddress** ([**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md))
* **Udp** ([**Udp**](class_udp.md))
* **UdpMsg** ([**UdpMsg**](struct_udp_msg.md))
* **UdpProtocol** ([**UdpProtocol**](class_udp_protocol.md))
* **UpdateNetworkStats** ([**UdpProtocol**](class_udp_protocol.md))


## v

* **void** ([**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md))
* **value** ([**GameInput**](struct_game_input.md))


## ~

* **~ConnectionInfo** ([**ConnectionInfo**](class_connection_info.md))
* **~ConnectionManager** ([**ConnectionManager**](class_connection_manager.md))
* **~GGPOSession** ([**GGPOSession**](struct_g_g_p_o_session.md))
* **~IPollSink** ([**IPollSink**](class_i_poll_sink.md))
* **~InputQueue** ([**InputQueue**](class_input_queue.md))
* **~Peer2PeerBackend** ([**Peer2PeerBackend**](class_peer2_peer_backend.md))
* **~SpectatorBackend** ([**SpectatorBackend**](class_spectator_backend.md))
* **~Sync** ([**Sync**](class_sync.md))
* **~SyncTestBackend** ([**SyncTestBackend**](class_sync_test_backend.md))
* **~TimeSync** ([**TimeSync**](class_time_sync.md))
* **~Callbacks** ([**Udp::Callbacks**](struct_udp_1_1_callbacks.md))
* **~Udp** ([**Udp**](class_udp.md))
* **~UdpProtocol** ([**UdpProtocol**](class_udp_protocol.md))




