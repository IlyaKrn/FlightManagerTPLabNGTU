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
import java.util.List;
import java.util.Set;

@Service
public class AuthService {

    @Autowired
    private UserRepo userRepo;
    @Autowired
    private JwtUtil jwt;

    public TokenResponse login(String email, String password) {
        UserModel u = userRepo.getByEmail(email);
        if (u == null)
            return null;
        if (!password.equals(u.getPassword()))
            return null;
        return new TokenResponse(u.getId(), jwt.generateToken(new UserAuth(u.getId(), u.getEmail(), u.getPassword(), u.getRoles())));
    }

    public TokenResponse register(UserModel data) {
        UserModel u = userRepo.create(data);
        u.setRoles(Collections.singleton(RoleModel.DISPATCHER));
        u.setIsBanned(false);
        return new TokenResponse(u.getId(), jwt.generateToken(new UserAuth(u.getId(), u.getEmail(), u.getPassword(), u.getRoles())));
    }

    public boolean authorize(String token, Set<String> permissions) {
        return !jwt.isTokenExpired(token) && userRepo.getById(Long.parseLong(jwt.extractId(token))) != null;
    }

    public Long getIdFromToken(String token) {
        if (jwt.isTokenExpired(token))
            return null;
        return Long.parseLong(jwt.extractId(token));
    }

}
