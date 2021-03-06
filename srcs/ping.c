/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:31:16 by adbenoit          #+#    #+#             */
/*   Updated: 2022/07/18 14:09:02 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	set_status(void)
{
	if (g_data.flag.count == g_data.stats.nsent
		|| g_data.stats.nsent == LLONG_MAX)
		g_data.status |= STOP_SENDING;
	if (g_data.flag.count == g_data.stats.nrecv)
		g_data.status &= ~WAIT_REPLY;
	g_data.status &= ~RTIMEDOUT;
}

static void	ping_output(int code, long long int n)
{
	char	src[INET_ADDRSTRLEN];
	char	dst[INET_ADDRSTRLEN];

	if (code == ETIMEDOUT) {
		if (FLAG_ISSET(F_VERBOSE))
			printf("Request timeout for icmp_seq %lld\n", n);
		return ;
	}
	if (!inet_ntop(AF_INET, &R_PACKET.iphdr.ip_src, src, INET_ADDRSTRLEN))
		ft_perror(ft_strerror(errno), "inet_ntop");
	if (!inet_ntop(AF_INET, &R_PACKET.iphdr.ip_dst, dst, INET_ADDRSTRLEN))
		ft_perror(ft_strerror(errno), "inet_ntop");
	if (code == SUCCESS) {
		printf("%zd bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3f ms\n",
			sizeof(struct s_request), g_data.host, src,
			R_PACKET.icmphdr.icmp_seq, R_PACKET.iphdr.ip_ttl,
			g_data.time_ms);
		return ;
	}
	else {
		printf("From %s icmp_seq=%lld %s\n", src, n, icmp_strerror(code));
		print_iphdr(R_PACKET.iphdr);
	}
}

void	ping(void)
{
	struct timeval	req_time;
	int				ret;

	printf("PING %s (%s) %d(%d) bytes of data.\n", g_data.host, g_data.ip,
		PACKET_SIZE, PACKET_SIZE + HEADER_SIZE);
	g_data.request_packet = request_packet();
	while (STATUS_ISSET(WAIT_REPLY) || !STATUS_ISSET(STOP_SENDING))
	{
		if (!STATUS_ISSET(WAIT_REPLY)) {
			send_echo_request(&req_time);
			g_data.status |= WAIT_REPLY;
		}
		alarm(TIMEOUT);
		ret = recv_echo_reply(req_time);
		if (!FLAG_ISSET(F_QUIET) && ret != EP_BADPACK)
			ping_output(ret, g_data.stats.nsent);
		set_status();
		if (!STATUS_ISSET(WAIT_REPLY) && !STATUS_ISSET(STOP_SENDING))
			ft_wait(req_time, TIME_INTERVAL);
	}
	print_statistics();
}
