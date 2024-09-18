package com.flightmanager.databaseservice.repos;

import com.flightmanager.databaseservice.models.DispatcherModel;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface DispatcherRepo extends JpaRepository<DispatcherModel, Long> {
    Optional<DispatcherModel> findByEmail(String email);
}
