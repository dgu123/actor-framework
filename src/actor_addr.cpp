/******************************************************************************\
 *           ___        __                                                    *
 *          /\_ \    __/\ \                                                   *
 *          \//\ \  /\_\ \ \____    ___   _____   _____      __               *
 *            \ \ \ \/\ \ \ '__`\  /'___\/\ '__`\/\ '__`\  /'__`\             *
 *             \_\ \_\ \ \ \ \L\ \/\ \__/\ \ \L\ \ \ \L\ \/\ \L\.\_           *
 *             /\____\\ \_\ \_,__/\ \____\\ \ ,__/\ \ ,__/\ \__/.\_\          *
 *             \/____/ \/_/\/___/  \/____/ \ \ \/  \ \ \/  \/__/\/_/          *
 *                                          \ \_\   \ \_\                     *
 *                                           \/_/    \/_/                     *
 *                                                                            *
 * Copyright (C) 2011-2013                                                    *
 * Dominik Charousset <dominik.charousset@haw-hamburg.de>                     *
 *                                                                            *
 * This file is part of libcppa.                                              *
 * libcppa is free software: you can redistribute it and/or modify it under   *
 * the terms of the GNU Lesser General Public License as published by the     *
 * Free Software Foundation; either version 2.1 of the License,               *
 * or (at your option) any later version.                                     *
 *                                                                            *
 * libcppa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with libcppa. If not, see <http://www.gnu.org/licenses/>.            *
 \******************************************************************************/


#include "cppa/actor.hpp"
#include "cppa/actor_addr.hpp"
#include "cppa/local_actor.hpp"

#include "cppa/detail/raw_access.hpp"

namespace cppa {

namespace {
intptr_t compare_impl(const abstract_actor* lhs, const abstract_actor* rhs) {
    return reinterpret_cast<intptr_t>(lhs) - reinterpret_cast<intptr_t>(rhs);
}
} // namespace <anonymous>

actor_addr::actor_addr(const actor& other) : m_ops(detail::raw_access::get(other)) { }

actor_addr::actor_addr(const invalid_actor_addr_t&) : m_ops(nullptr) { }

actor_addr::actor_addr(abstract_actor* ptr) : m_ops(ptr) { }

actor_addr::operator bool() const {
    return static_cast<bool>(m_ops.m_ptr);
}

bool actor_addr::operator!() const {
    return !(m_ops.m_ptr);
}

intptr_t actor_addr::compare(const actor& other) const {
    return compare_impl(m_ops.m_ptr.get(), detail::raw_access::get(other));
}

intptr_t actor_addr::compare(const actor_addr& other) const {
    return compare_impl(m_ops.m_ptr.get(), other.m_ops.m_ptr.get());
}

intptr_t actor_addr::compare(const local_actor* other) const {
    return compare_impl(m_ops.m_ptr.get(), other);
}

} // namespace cppa