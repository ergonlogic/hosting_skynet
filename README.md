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


Installation
-----------

Install as you would any other Drupal module.


Configuration
-------------

Skynet requires a configuration file containing credentials to connect to
Aegir's database. This file should be at '~/config/skynet.conf' and look like:

    [database]
    host = localhost
    db = <aegir_site_db>
    user = <aegir_site_db_user>
    passwd = <aegir_site_db_password>

The creation of this config file is automated in a post-verify hook.


Usage
-----

Since Skynet is built on Cement, we are provided with a number of useful CLI
options by default, including a help option:

    $ ~/.drush/skynet/skynet.py -h

The only sub-command implemented so far is to run a queue daemon:

    $ ~/.drush/skynet/skynet.py queued

This command has a handy alias 'q', and can also be run in the background:

    $ ~/.drush/skynet/skynet.py q --daemon


--------------------------------------------------------------------------------
Author:    Christopher (ergonlogic) Gervais (mailto:chris@ergonlogic.com)
Copyright: Copyright (c) 2016 Ergon Logic Enteprises (http://ergonlogic.com)
License:   GPLv3 or later
