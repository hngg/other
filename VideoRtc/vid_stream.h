
#ifndef __PJMEDIA_VID_STREAM_H__
#define __PJMEDIA_VID_STREAM_H__


#include "types.h"
#include "rtp.h"
#include "rtcp.h"
#include "vid_port.h"

#include "jitter_buffer.h"
#include "transport_udp.h"


//#ifdef PJMEDIA_VIDEO_RESEND_OPTIMIZE
#define RTCP_NACK 205
#define RTCP_RR   201
#define RTCP_SR   200
#define RTCP_FIR   192 /* add by j33783 20190805 */
#define RTCP_SR_RR_FALG 1
#define RTCP_SDES_FALG (RTCP_SR_RR_FALG << 1)
#define RTCP_NACK_FALG (RTCP_SDES_FALG << 1)
#define RTCP_BYTE_FALG (RTCP_NACK_FALG << 1)
#define RTCP_FIR_FALG (RTCP_BYTE_FALG << 1)   /* add by j33783 20190805 */

#define RTP_PACKET_SEQ_MAP_MAX 17
#define HEARTBREAK_RTP_PT 127
#define TERMINAL_TYPE 5


#define RESEND_SUPPORT  1
//#define RESEND_ARR_MAX_NUM  64
//#define RESEND_HEARTBREAK_TYPE 306
//#define RESEND_HEARTBREAK_MAX_LEN 32
//#define RESEND_BREAKBEART_TIMES 3
//#define RESEND_TIMES_MAX 2
//#define RESEND_REQ_BASESEQ_BUFF_LEN 1024
//#define RESEND_BUFF_SIZE  1024


//#ifdef PJMEDIA_VIDEO_JBUF_OPTIMIZE
#define DISCARD_RESEND_NUM_MAX  30
#define DEC_FRAME_ARR_MAX       20
#define FRAME_LEN_MAX           720*1280*3/2
#define DELAY_FRAME_NUM         5
#define DELAY_FRAME_NUM_MAX     10
#define BEGIN_RENDER_FRAME_IDX  3
//#endif

#ifdef HYT_HEVC
#define H265_FRAME_MAX_SIZE  256*1920
#endif


typedef struct pjmedia_vid_stream
{
    transport_udp           *trans;
    
    pjmedia_format_id       fmt_id;
    unsigned                clock_rate;
    uint64_t                first_pts;
    float                   pts_ratio;
    pjmedia_rtp_session     rtp_session;
    pjmedia_vid_port        vid_port;
    RingBuffer*             ringbuf;          /**< Jitter buffer optimize.            */
    void* rtp_unpack_buf;
    void* rto_to_h264_obj;
    int                     codecType;
    on_network_status       network_cb;

    //unsigned		        out_rtcp_pkt_size;
    char		            out_rtcp_pkt[PJMEDIA_MAX_MTU];  /**< Outgoing RTCP packet.	    */
    
}pjmedia_vid_stream;


int packet_and_send_(struct pjmedia_vid_stream*stream, char* frameBuffer, int frameLen);


#endif	/* __PJMEDIA_VID_STREAM_H__ */
