# FT_PING (@42Paris)
*Recoding the ping command.*

## Usage

```
$ git clone https://github.com/adbenoit-9/42_ft_ping.git
$ cd 42_ft_ping
$ make
$ ./ft_ping [options] <destination>
```

### Description

<p style="margin: 0px; margin-top: 1em; margin-bottom: 1.5em;margin-left: 1em">
    Send ICMP ECHO_REQUEST packets to network hosts.
</p>

### Options

<p style="margin-top: 1em;">
    <strong>-c</strong> <ins>count</ins><br>
    Stop after sending count ECHO_REQUEST packets.<br><br>
    <strong>-h</strong><br>
    Show help.<br><br>
    <strong>-q</strong><br>
    Quiet output. Nothing is displayed except the summary lines at startup time and when finished.<br><br>
    <strong>-t</strong> <ins>ttl</ins><br>
    Set the IP Time to Live.<br><br>
    <strong>-v</strong><br>
    Verbose output.<br><br>
</p>

