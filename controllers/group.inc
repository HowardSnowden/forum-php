<?php
include_once "include/util.inc";
include_once "models/Group.inc";

function get_manage($params) {
    $groups = Group::findAll();
    // @formatter:off
    renderTemplate(
        "views/group_list.inc",
        array(
            "title" => "Manage groups",
            "groups" => $groups
        )
    );
    // @formatter:on
}

function post_add($params) {
    $group = safeParam($_REQUEST, 'group');
    $group = new Group($group);
    $validator = $group -> validate();
    if ($validator -> hasErrors()) {
        get_manage(null);
        exit();
    }
    $group -> insert();
    redirectRelative("group/manage");
}

function get_delete($params) {
    $id = safeParam($params, 0);
    if (!$id) {
        die("No ID specified");
    }
    $group = Group::findById($id);
    $group -> delete();
    redirectRelative("group/manage");
}

function get_members($params) {
    $id = safeParam($params, 0);
    if (!$id) {
        die("No id specified");
    }
    $group = Group::findById($id);
    $members = $group -> getMembers();
    $nonmembers = $group -> getNonMembers();
    // @formatter:off
    renderTemplate(
        "views/group_members.inc",
        array(
            "title" => "{$group->getName()} Group",
            "members" => $members,
            "nonmembers" => $nonmembers,
            "group" => $group
        )
    );
    // @formatter:on
}

function get_permissions($params) {
    $id = safeParam($params, 0);
    if (!$id) {
        die("No id specified");
    }
    $group = Group::findById($id);
    $permissions = $group -> getPermissions();
    $nonpermissions = $group -> getNonPermissions();
    // @formatter:off
    renderTemplate(
        "views/group_permissions.inc",
        array(
            "title" => "{$group->getName()} Group",
            "permissions" => $permissions,
            "nonpermissions" => $nonpermissions,
            "group" => $group
        )
    );
    // @formatter:on
}

function get_remove($params) {
    $groupId = safeParam($params, 0);
    $userId = safeParam($params, 1);

    $group = Group::findById($groupId);
    $user = User::findById($userId);

    if (!($group && $user)) {
        die("Expecting group and user id");
    }

    $group -> removeUser($user);
    redirectRelative("group/members/{$group->getId()}");
}

function get_include($params) {
    $groupId = safeParam($params, 0);
    $userId = safeParam($params, 1);

    $group = Group::findById($groupId);
    $user = User::findById($userId);

    if (!($group && $user)) {
        die("Expecting group and user id");
    }

    $group -> addUser($user);
    redirectRelative("group/members/{$group->getId()}");
}

function get_grant($params) {
    $groupId = safeParam($params, 0);
    $permissionId = safeParam($params, 1);

    $group = Group::findById($groupId);
    $permission = Permission::findById($permissionId);

    if (!($group && $permission)) {
        die("Expecting group and permission id");
    }

    $group -> addPermission($permission);
    redirectRelative("group/permissions/{$group->getId()}");
}

function get_revoke($params) {
    $groupId = safeParam($params, 0);
    $permissionId = safeParam($params, 1);

    $group = Group::findById($groupId);
    $permission = Permission::findById($permissionId);

    if (!($group && $permission)) {
        die("Expecting group and permission id");
    }

    $group -> removePermission($permission);
    redirectRelative("group/permissions/{$group->getId()}");

}
?>