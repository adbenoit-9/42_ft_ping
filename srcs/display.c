/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:42:51 by adbenoit          #+#    #+#             */
/*   Updated: 2022/07/16 18:19:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	print_usage(void)
{
	printf("\nUsage\n");
	printf(" ./ft_ping [options] <destination>\n");
	printf("\nOptions:\n");
	printf("-h                 print help and exit\n");
	printf("-v                 verbose output\n");
	printf("-c <count>         stop after <count> replies\n");
	printf("-q                 quiet output\n");
	printf("\n");
	return (0);
}

int	print_packet(t_packet packet, long long int n)
{
	char	src[INET_ADDRSTRLEN];
	char	dst[INET_ADDRSTRLEN];
	int		len;


	if (sizeof(packet) == sizeof(R_PACKET))
	{
		if (!inet_ntop(AF_INET, &R_PACKET.iphdr.ip_src, src, INET_ADDRSTRLEN))
			ft_perror(ft_strerror(errno), "inet_ntop");
		if (!inet_ntop(AF_INET, &R_PACKET.iphdr.ip_dst, dst, INET_ADDRSTRLEN))
			ft_perror(ft_strerror(errno), "inet_ntop");
		printf("From %s icmp_seq=%lld Time to live exceeded\n", src, n);
		len = ft_strlen(src);
		if (FLAG_ISSET(F_VERBOSE)) {
			printf("%2s %2s %3s %5s %5s %4s %3s %3s %4s %*s %*s\n",
				"Vr", "HL", "TOS", "Len", "ID", "off", "TTL", "Pro",
				"cks", len - len / 2, "Src", len, "Dst");
			printf("%2d %2d %3d %5d %5d %.4d %3.2d %3.2d %4x %s %2s\n\n",
				packet.echo.reply.iphdr.ip_v, packet.echo.reply.iphdr.ip_hl,
				packet.echo.reply.iphdr.ip_tos, packet.echo.reply.iphdr.ip_len,
				packet.echo.reply.iphdr.ip_id, packet.echo.reply.iphdr.ip_off,
				packet.echo.reply.iphdr.ip_ttl, packet.echo.reply.iphdr.ip_p,
				packet.echo.reply.iphdr.ip_sum,
				src, dst);
		}
	}
	return (0);
}

void	print_rtt(void)
{
	double	avg;
	double	stddev;

	avg = g_data.stats.sum_time / g_data.stats.nrecv;
	stddev = standard_deviation(g_data.stats.sum_time,
		g_data.stats.sum_square_time, g_data.stats.nrecv);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
		g_data.stats.min_time, avg, g_data.stats.max_time, stddev);
}

void	print_statistics(void)
{
	struct timeval	end_time;
	double			sum_time;
	double			loss_ratio;

	if (gettimeofday(&end_time, NULL) == -1)
		fatal_error(errno, "gettimeofday", 0);
	sum_time = tv_to_ms(end_time) - tv_to_ms(g_data.stats.begin_time);
	printf("--- %s ping statistics ---\n", g_data.host);
	loss_ratio = 0;
	if (g_data.stats.nsent)
		loss_ratio = (double)(g_data.stats.nsent - g_data.stats.nrecv) / g_data.stats.nsent;
	if (!g_data.stats.nerror) {
		printf("%lld packets transmitted, %lld packets received, %ld%c packet loss, time %dms\n",
			g_data.stats.nsent, g_data.stats.nrecv, (size_t)(loss_ratio * 100),
			'%', (int)sum_time);
	}
	else {
		printf("%lld packets transmitted, %lld packets received, +%lld errors, %ld%c packet loss, time %dms\n",
			g_data.stats.nsent, g_data.stats.nrecv, g_data.stats.nerror,
			(size_t)(loss_ratio * 100), '%', (int)sum_time);
	}
	if (g_data.stats.nrecv)
		print_rtt();
	clean();
	exit(SUCCESS);
}
