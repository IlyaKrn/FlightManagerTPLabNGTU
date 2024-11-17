package com.flightmanager.identityservice.service;

import com.flightmanager.identityservice.jwt.JwtUtil;
import com.flightmanager.identityservice.jwt.UserAuth;
import com.flightmanager.identityservice.models.RoleModel;
import com.flightmanager.identityservice.models.TokenResponse;
import com.flightmanager.identityservice.models.UserModel;
import com.flightmanager.identityservice.repo.UserRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Service
public class AuthService {

    @Autowired
    private UserRepo userRepo;
    @Autowired
    private JwtUtil jwt;

    public TokenResponse login(String email, String password) {
        List<UserModel> us = userRepo.getByEmail(email);
        UserModel u = null;
        if (us != null && !us.isEmpty())
            u = us.get(0);
        if (u == null)
            return null;
        if (!password.equals(u.getPassword()))
            return null;
        return new TokenResponse(u.getId(), jwt.generateToken(new UserAuth(u.getId(), u.getEmail(), u.getPassword(), u.getRoles())));
    }

    public TokenResponse register(UserModel data) {
        List<UserModel> us = userRepo.getByEmail(data.getEmail());
        UserModel u = null;
        if (us != null && !us.isEmpty())
            u = us.get(0);
        if (u != null)
            return null;
        data.setRoles(Collections.singleton(RoleModel.DISPATCHER));
        data.setIsBanned(false);
        u = userRepo.create(data);
        return new TokenResponse(u.getId(), jwt.generateToken(new UserAuth(u.getId(), u.getEmail(), u.getPassword(), u.getRoles())));
    }

    public boolean authorize(String token, Set<String> permissions) {
        try {
            if (permissions == null || permissions.isEmpty())
                return true;
            if (token == null || jwt.extractId(token) == null || jwt.isTokenExpired(token))
                return false;
            UserModel u = userRepo.getById(Long.parseLong(jwt.extractId(token))).get(0);
            if (u == null)
                return false;

            Set<String> permsForDispatcher = new HashSet<>();
            Set<String> permsForAdmin = new HashSet<>();

            permsForDispatcher.add("airport-get");
            permsForDispatcher.add("airport-create");
            permsForDispatcher.add("airport-update");
            permsForDispatcher.add("airport-delete");

            permsForDispatcher.add("plane-get");
            permsForDispatcher.add("plane-create");
            permsForDispatcher.add("plane-update");
            permsForDispatcher.add("plane-delete");

            permsForDispatcher.add("flight-get");
            permsForDispatcher.add("flight-create");

            permsForDispatcher.add("time-get");
            permsForDispatcher.add("time-skip");

            permsForDispatcher.add("dispatcher-get-public " + u.getId());
            permsForDispatcher.add("dispatcher-get-private " + u.getId());

            permsForDispatcher.add("dispatcher-update-public " + u.getId());
            permsForDispatcher.add("dispatcher-update-private " + u.getId());

            permsForAdmin.add("dispatcher-get-public");
            permsForAdmin.add("dispatcher-get-private " + u.getId());

            permsForAdmin.add("dispatcher-update-public");
            permsForAdmin.add("dispatcher-update-private " + u.getId());

            for (String p : permissions) {
                if (permsForDispatcher.contains(p) && u.getRoles().contains(RoleModel.DISPATCHER)) {
                    continue;
                }
                if (permsForAdmin.contains(p) && u.getRoles().contains(RoleModel.ADMIN)) {
                    continue;
                }
                if (permsForDispatcher.contains(p) && permsForAdmin.contains(p) && (u.getRoles().contains(RoleModel.DISPATCHER) || u.getRoles().contains(RoleModel.ADMIN))) {
                    continue;
                }
                return false;
            }
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public Long getIdFromToken(String token) {
        if (jwt.isTokenExpired(token) || jwt.extractId(token) == null)
            return null;
        return Long.parseLong(jwt.extractId(token));
    }

}
