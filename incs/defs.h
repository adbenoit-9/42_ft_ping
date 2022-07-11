/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:45:31 by adbenoit          #+#    #+#             */
/*   Updated: 2022/07/11 02:28:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H

/*
** -- Includes --
*/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sysexits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <signal.h>
# include <arpa/inet.h>
# include <ctype.h>
# include <netinet/ip_icmp.h>
# include <stdbool.h>

# define DEBUG 1
# define TIME_INTERVAL 1
# define LLONG_MAX 9223372036854775807
# define send_packet icmp_packet.echo.request
# define recv_packet icmp_packet.echo.reply

/*
** -- Flags --
*/
# define NB_FLAGS 4
# define FLAGS "hvcq"
# define HELP 0x80
# define VERBOSE 0x40
# define COUNT 0x20
# define QUIET 0x10

/*
** -- Packet info --
*/
# define HEADER_SIZE 28
# define PACKET_SIZE 56
# define TOTAL_SIZE PACKET_SIZE + HEADER_SIZE
# define ECHO_REQUEST_TYPE 8
# define ECHO_REQUEST_CODE 0
# define DEFAULT_TTL 64
# define VERSION 4

/*
** -- Exit code --
*/
# define SUCCESS 0
# define USAGE_ERR 1
# define ERROR 2

/*
** -- Error code --
*/
# define NOMEM 0
# define SOCKERR 1
# define NOHOST 2
# define BADHOST 3
# define BADAF 4
# define BADARG 5
# define BADOPT 6
# define ARGOOR 7

/*
** -- Error message --
*/
# define NOMEM_MSG "ft_ping: out of memory\n"
# define SOCKERR_MSG "ft_ping: socket error\n"
# define NOHOST_MSG "ft_ping: usage error: Destination address required\n"
# define BADHOST_MSG "ft_ping: %s: Name or service not known\n"
# define BADAF_MSG "ft_ping: %s: Address family for hostname not supported\n"
# define BADARG_MSG  "ft_ping: invalid agument: '%s'\n"
# define BADOPT_MSG "ft_ping: invalid option -- %c\n"
# define ARGOOR_MSG  "ft_ping: invalid agument: '%s': out of range: %d <= value <= %ld\n"

#endif
