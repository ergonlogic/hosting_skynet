Skynet
======

Skynet is an experimental replacement for the Aegir Hosting System's Queue
Daemon. It is written in Python using Cement (http://builtoncement.org).

It is currently pretty basic, but used in production by several Aegir
maintainers.
 
Dependencies
------------

Install pip, VirtualEnv and cement:

    # apt-get install python-pip python-dev build-essential python-mysqldb
    # pip install --upgrade pip
    # pip install --upgrade virtualenv
    # pip install cement

In addition to the above dependencies of the Skynet Python script, the use of
Supervisor is highly recommended to ensure the Daemon continues running
reliably. Installation should be as simple as:

    # apt-get install supervisor


Installation
------------

Install as you would any other Drupal module. Enable it via the Hosting
Features pages. This will trigger a verify task for the Hostmaster site. Upon
completion of that task, the configuration for running the Skynet daemon should
be in place.

All that should be left at that point is to drop the provided Supervisor config
script into place and restart Supervisor:

    # cp /path/to/hostmaster/platform/skynet/module/drush/skynet.supervisor.conf /etc/supervisor/conf.d/
    # service supervisor restart

Confirm that the service is running:

    # supervisorctl status skynet-queue
    skynet-queue                     RUNNING    pid 16047, uptime 0:18:13


Configuration
-------------

Skynet requires a configuration file containing credentials to connect to
Aegir's database. This file should be at '~/config/skynet/skynet.conf' and look like:

    [database]
    host = localhost
    db = <aegir_site_db>
    user = <aegir_site_db_user>
    passwd = <aegir_site_db_password>

The creation of this config file is automated in a post-verify hook on the
hostmaster site.


Usage
-----

Generally, you'll want to run the Skynet Daemon via Supervisor or the like.
However, it can be run manually. Since Skynet is built on Cement, we are
provided with a number of useful CLI options by default, including a help
option:

    $ /var/aegir/config/skynet/skynet.py -h

The only sub-command implemented so far is to run a queue daemon:

    $ /var/aegir/config/skynet/skynet.py queued

This command has a handy alias 'q', and can also be run in the background:

    $ /var/aegir/config/config/skynet/skynet.py q --daemon


--------------------------------------------------------------------------------
Author:    Christopher (ergonlogic) Gervais (mailto:chris@ergonlogic.com)
Copyright: Copyright (c) 2016 Ergon Logic Enteprises (http://ergonlogic.com)
License:   GPLv3 or later
